#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <event.h>
#include <pthread.h>
#include <libtoolkit/list.h>
#include <libtoolkit/kref.h>
#include <libtoolkit/bitops.h>
#include <libtoolkit/spinlock.h>
#include <libtoolkit/common.h>

#include "common.h"
#include "config.h"
#include "main.h"
#include "dev.h"
#include "rpc.h"
#include "cache.h"
#include "compact.h"
#include "timer.h"
#include "office.h"
#include "office_ctl.h"
#include "his.h"
#include "protocol/cobaya.pb.h"

namespace cobaya {

struct FlowHead {
	list_head head;

	int item_code;
	OfficeCtl *office;

	list_head list;
	spinlock_t lock;
};

struct FlowDesc {
#define FLOW_REMOVE	(0x1 << 1)
#define FLOW_ITEDEL	(0x1 << 2)
#define FLOW_WATCH	(0x1 << 3)
#define FLOW_ACTIVE	(0x1 << 4)
#define FLOW_EVENT	(0x1 << 5)
	unsigned long flags;

	kref ref;
	FlowHead *owner;
	list_head list;

	timespec start;
	event life_event;

	uint64_t user_id;
	uint32_t office_id;
	char apply_id[APPLY_ID];
	char user[USER_NAME];
	char doctor[USER_NAME];

	int valid;
	ItemDesc *items[ITEM_CHILD];
};

static DEFINE_LIST_HEAD(flow_head);
static cache_t *flow_cache;

struct ThreadCtx {
	int send_fd;
	int recv_fd;
	event recv_ev;

	list_head list;
};

static DEFINE_LIST_HEAD(thr_list);
static pthread_mutex_t thr_mutex = PTHREAD_MUTEX_INITIALIZER;

static void __del_flow(kref *ref)
{
	FlowHead *head;
	FlowDesc *flow;

	flow = container_of(ref, FlowDesc, ref);
	head = flow->owner;

	spin_lock(&head->lock);
	list_del(&flow->list);
	spin_unlock(&head->lock);

	cache_free(flow_cache, flow);
}

static void handle_flow_timeout(int fd, short ev, void *arg)
{
	bool del_all = true;
	FlowDesc *flow = (FlowDesc *)arg;

	spin_lock(&flow->owner->lock);
	flow->flags |= FLOW_REMOVE;
	if (flow->flags & FLOW_ITEDEL) {
		del_all = false;
	}
	spin_unlock(&flow->owner->lock);

	if (del_all) {
		while (!kref_put(&flow->ref, __del_flow));
	} else {
		kref_put(&flow->ref, __del_flow);
	}
}

static void handle_flow_monitor(int fd, short ev, void *arg)
{
	FlowDesc *flow;
	ThreadCtx *ctx = (ThreadCtx *)arg;

	if (read(ctx->recv_fd, &flow, sizeof(flow)) != sizeof(flow)) {
		DUMP_LOG("failed reading from notify pipe");
		return;
	}

	if ((flow->flags & FLOW_WATCH) && !(flow->flags & FLOW_EVENT)) {
		timeval tv;

		tv.tv_usec = 0;
		tv.tv_sec = g_config.watch_flow_life * 60;

		if (evtimer_assign(&flow->life_event, main_base,
	     			   handle_flow_timeout, flow)) {
			DUMP_LOG("evtimer_assign() error");
			goto err_watch;
		}
		if (evtimer_add(&flow->life_event, &tv)) {
			DUMP_LOG("evtimer_add() error");
			goto err_watch;
		}

		flow->flags |= FLOW_EVENT;
		return;
err_watch:
		spin_lock(&flow->owner->lock);
		flow->flags &= ~FLOW_WATCH;
		spin_unlock(&flow->owner->lock);

		kref_put(&flow->ref, __del_flow);
		return;
	}

	if (flow->flags & FLOW_ACTIVE) {
		event_active(&flow->life_event, EV_TIMEOUT, 0);
		kref_put(&flow->ref, __del_flow);
	}
}

int load_flow_monitor()
{
	int err = 0, fd[2];
	ThreadCtx *ctx;

	if (!g_config.watch_allow)
		return 0;

	if (pipe2(fd, O_CLOEXEC)) {
		DUMP_LOG("pipe2() error");
		return -1;
	}
	ctx = (ThreadCtx *)malloc(sizeof(*ctx));
	if (ctx == NULL) {
		DUMP_LOG("no memory");
		err = -1;
		goto close;
	}
	memset(ctx, 0, sizeof(*ctx));
	ctx->send_fd = fd[1];
	ctx->recv_fd = fd[0];
	INIT_LIST_HEAD(&ctx->list);

	pthread_mutex_lock(&thr_mutex);

	if (notify_fd != 0) {
		DUMP_LOG("should be called once for each thread");
		pthread_mutex_unlock(&thr_mutex);
		err = -1;
		goto free;
	}
	if (event_assign(&ctx->recv_ev, main_base,
			 ctx->recv_fd, EV_READ | EV_PERSIST,
			 handle_flow_monitor, ctx)) {
		DUMP_LOG("event_assign() error");
		pthread_mutex_unlock(&thr_mutex);
		err = -1;
		goto free;
	}
	if (event_add(&ctx->recv_ev, NULL)) {
		DUMP_LOG("event_add() error");
		pthread_mutex_unlock(&thr_mutex);
		err = -1;
		goto free;
	}

	notify_fd = ctx->send_fd;
	list_add(&ctx->list, &thr_list);

	pthread_mutex_unlock(&thr_mutex);

	return 0;

free:
	free(ctx);
close:
	close(fd[0]);
	close(fd[1]);
	return err;
}

static int get_officectl_items()
{
	int items = 0;

	for (OfficeCtl *office = officectl_head.next;
	     office != &officectl_head; office = office->next) {
		char *p = office->items;
		char *end = office->items + OFFICE_ITEM;

		for (; p < end; p++) {
			if (*p == '_') items++;
		}
	}

	return items;
}

int load_flow_manager()
{
	int count = 0, i = 0;
	FlowHead *flows;

	count = get_officectl_items();
	flows = (FlowHead *)calloc(count, sizeof(*flows));
	if (flows == NULL) {
		DUMP_LOG("no memory");
		return -1;
	}

	for (OfficeCtl *office = officectl_head.next;
	     office != &officectl_head; office = office->next) {
		char *p = office->items;
		char *end = office->items + OFFICE_ITEM;

		for (; p < end; p++) {
			FlowHead *flow;

			if (*p != '_') {
				continue;
			} else {
				p++;
			}

			flow = flows + i;
			flow->item_code = ITEM_HEAD(p);
			flow->office = office;
			INIT_LIST_HEAD(&flow->head);
			INIT_LIST_HEAD(&flow->list);
			spin_lock_init(&flow->lock);

			office->head[flow->item_code] = flow;

			list_add(&flow->head, &flow_head);
			i++;
		}
	}

	for (DevDesc *dev = dev_head.next;
	     dev != &dev_head; dev = dev->next) {
		FlowHead *flow;
		bool find = false;

		list_for_each_entry(flow, &flow_head, head) {
			if (dev->item_code != flow->item_code) {
				continue;
			}
			if (strcmp(dev->office_id, flow->office->strid)) {
				continue;
			}
			find = true;
			dev->head = flow;
			break;
		}

		if (!find) {
			DUMP_LOG("无效设备 (%s:%s:%s)",
				dev->code, dev->name, dev->host);
			return -1;
		}
	}

	flow_cache = cache_create("flow_cache", sizeof(FlowDesc),
				  0, NULL, NULL);
	if (flow_cache == NULL) {
		DUMP_LOG("no memory");
		return -1;
	}

	return 0;
}

static inline ItemDesc* head_search(rb_root *root, uint32_t item_id)
{
	rb_node *node = root->rb_node;

	while (node) {
		ItemDesc *data = container_of(node, ItemDesc, node);
		int res;

		res = item_id - data->id;

		if (res < 0)
  			node = node->rb_left;
		else if (res > 0)
  			node = node->rb_right;
		else
  			return data;
	}
	return NULL;
}

static inline FlowHead* get_flow_head(const HisDesc *his, ItemDesc **item)
{
	FlowHead *head = NULL;

	for (OfficeCtl *office = officectl_head.next;
	     office != &officectl_head; office = office->next) {
		if (office->id != his->exe_office_id) {
			continue;
		}
		*item = head_search(&office->tree, his->item_id);
		if (*item != NULL) {
			head = (FlowHead *)office->head[(*item)->code];
		} else {
			DUMP_LOG("[cobaya.监控科室] %s:%s 不存在执行项目%d",
				 office->strid, office->name, his->item_id);
		}
		break;
	}
	return head;
}

bool new_flow(const HisDesc *his)
{
	bool res = true, has = false;
	ItemDesc *item;
	FlowHead *head;
	FlowDesc *desc, *pos;

	/* which flow head */
	head = get_flow_head(his, &item);
	if (unlikely(head == NULL)) {
		res = false;
		goto out;
	}

	/* add before */
	spin_lock(&head->lock);
	list_for_each_entry(pos, &head->list, list) {
		if (pos->user_id == his->user_id) {
			desc = pos;
			has = true;
			break;
		}
	}
	if (has) {
		bool add = true;
		for (int i = 0; i < desc->valid; i++) {
			if (desc->items[i] == item) {
				add = false;
				break;
			}
		}
		if (add) {
			desc->items[desc->valid++] = item;
		}
	}
	spin_unlock(&head->lock);

	/* first time add */
	if (has)
		goto out;
	desc = (FlowDesc *)cache_alloc(flow_cache);
	if (desc == NULL) {
		DUMP_LOG("no memory");
		res = false;
		goto out;
	}
	memset(desc, 0, sizeof(*desc));

	desc->owner = head;
	kref_init(&desc->ref);
	INIT_LIST_HEAD(&desc->list);
	desc->user_id = his->user_id;
	desc->office_id = his->app_office_id;
	strcpy(desc->apply_id, his->apply_id);
	strcpy(desc->user, his->user);
	strcpy(desc->doctor, his->doctor);
	desc->items[desc->valid++] = item;

	if (clock_gettime(CLOCK_MONOTONIC, &desc->start)) {
		cache_free(flow_cache, desc);
		res = false;
		DUMP_LOG("clock_gettime() error");
		goto out;
	}

	/* add new flow, check again */
	spin_lock(&head->lock);
	list_for_each_entry(pos, &head->list, list) {
		if (pos->user_id == his->user_id) {
			desc = pos;
			has = true;
			break;
		}
	}
	if (has) {
		bool add = true;
		for (int i = 0; i < desc->valid; i++) {
			if (desc->items[i] == item) {
				add = false;
				break;
			}
		}
		if (add) {
			desc->items[desc->valid++] = item;
		}
	} else {
		list_add_tail(&desc->list, &head->list);
	}
	spin_unlock(&head->lock);

	if (has) {
		cache_free(flow_cache, desc);
		res = false;
		DUMP_LOG("user(id = %lu) already add before", his->user_id);
	}

out:	return res;
}

void del_flow(const HisDesc *his)
{
	ItemDesc *item;
	FlowHead *head;
	FlowDesc *pos, *n, *flow = NULL;
	bool active = false, del = false;

	/* which flow head */
	head = get_flow_head(his, &item);
	if (unlikely(head == NULL)) {
		return;
	}

	spin_lock(&head->lock);
	list_for_each_entry_safe(pos, n, &head->list, list) {
		if (pos->user_id != his->user_id) {
			continue;
		}
		flow = pos;

		for (int i = 0; i < flow->valid; i++) {
			if (flow->items[i] != item) {
				continue;
			}

			for (int j = i; j < flow->valid; j++) {
				flow->items[j] = flow->items[j+1];
			}
			flow->valid--;
		}
		if (flow->valid) {
			spin_unlock(&head->lock);
			return;
		}

		if (!g_config.watch_allow) {
			list_del(&flow->list);
			del = true;
		} else {
			if (!(flow->flags & FLOW_WATCH)) {
				list_del(&flow->list);
				del = true;
				break;
			}
			if (flow->flags & FLOW_REMOVE) {
				break;
			} else {
				flow->flags |= FLOW_ITEDEL;
			}
			if (!(flow->flags & FLOW_ACTIVE)) {
				kref_get(&flow->ref);
				flow->flags |= FLOW_ACTIVE;
				active = true;
			}
		}

		break;
	}
	spin_unlock(&head->lock);

	if (del) {
		cache_free(flow_cache, flow);
	}
	if (active && (write(notify_fd, &flow, sizeof(flow)) != sizeof(flow))) {
		kref_put(&flow->ref, __del_flow);
		DUMP_LOG("failed writing notify pipe");
	}
	if (active) {
		kref_put(&flow->ref, __del_flow);
	}
}

void del_flow(void *_head, uint64_t user_id)
{
	FlowHead *head = (FlowHead *)_head;
	FlowDesc *pos, *n, *flow = NULL;
	bool active = false, del = false;

	spin_lock(&head->lock);
	list_for_each_entry_safe(pos, n, &head->list, list) {
		if (pos->user_id != user_id)
			continue;
		flow = pos;
		if (!g_config.watch_allow) {
			list_del(&flow->list);
			del = true;
		} else {
			if (!(flow->flags & FLOW_WATCH)) {
				list_del(&flow->list);
				del = true;
				break;
			}
			if (flow->flags & FLOW_REMOVE) {
				break;
			} else {
				flow->flags |= FLOW_ITEDEL;
			}
			if (!(flow->flags & FLOW_ACTIVE)) {
				kref_get(&flow->ref);
				flow->flags |= FLOW_ACTIVE;
				active = true;
			}
		}

		break;
	}
	spin_unlock(&head->lock);

	if (del) {
		cache_free(flow_cache, flow);
	}
	if (active && (write(notify_fd, &flow, sizeof(flow)) != sizeof(flow))) {
		kref_put(&flow->ref, __del_flow);
		DUMP_LOG("failed writing notify pipe");
	}
	if (active) {
		kref_put(&flow->ref, __del_flow);
	}
}

bool hit_flow(void *_head, uint64_t user_id)
{
	FlowHead *head = (FlowHead *)_head;
	FlowDesc *pos, *flow = NULL;
	bool watch = false;

	spin_lock(&head->lock);
	list_for_each_entry(pos, &head->list, list) {
		if (pos->user_id != user_id)
			continue;
		flow = pos;
		if (!(flow->flags & FLOW_WATCH) &&
		    g_config.watch_allow) {
			flow->flags |= FLOW_WATCH;
			kref_get(&flow->ref);
			watch = true;
		}
		break;
	}
	spin_unlock(&head->lock);

	if (watch && (write(notify_fd, &flow, sizeof(flow)) != sizeof(flow))) {
		spin_lock(&head->lock);
		flow->flags &= ~FLOW_WATCH;
		spin_unlock(&head->lock);

		kref_put(&flow->ref, __del_flow);
		DUMP_LOG("failed writing notify pipe");
	}

	return (flow != NULL);
}

void get_flow(void *_head, MsgFetchFlowRsp *rsp)
{
	FlowDesc *pos;
	FlowHead *head = (FlowHead *)_head;

	spin_lock(&head->lock);
	list_for_each_entry(pos, &head->list, list) {
		if (pos->flags & (FLOW_REMOVE | FLOW_ITEDEL | FLOW_WATCH)) {
			continue;
		}

		UserFlow *flow = rsp->add_flows();
		if (!flow) {
			DUMP_LOG("no memory");
			break;
		}

		flow->set_user_id(pos->user_id);
		flow->set_apply_id(pos->apply_id);
		flow->set_user(pos->user);
		flow->set_office(offices[pos->office_id].name);
		flow->set_doctor(pos->doctor);
		for (int i = 0; i < pos->valid; i++) {
			flow->add_items(pos->items[i]->name);
		}
	}
	spin_unlock(&head->lock);
}

void remove_expire_flow()
{
	FlowHead *head;

	list_for_each_entry(head, &flow_head, head) {
		FlowDesc *pos, *n;
		DEFINE_LIST_HEAD(del);

		spin_lock(&head->lock);
		list_for_each_entry_safe(pos, n, &head->list, list) {
			if (pos->flags & FLOW_WATCH)
				continue;
			if (pos->start.tv_sec <= old_flow.tv_sec) {
				list_move(&pos->list, &del);
			}
		}
		spin_unlock(&head->lock);

		list_for_each_entry_safe(pos, n, &del, list) {
			list_del(&pos->list);
			cache_free(flow_cache, pos);
		}
	}
}

} // namespace cobaya
