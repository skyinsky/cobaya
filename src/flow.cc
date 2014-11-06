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

namespace cobaya {

#define ULEN	11

struct FlowHead {
	list_head head;
	char host[DEV_HOST];

	list_head list;
	spinlock_t lock;
};

struct FlowDesc {
#define FLOW_WATCH	(0x1 << 1)
#define FLOW_ACTIVE	(0x1 << 2)
#define FLOW_EVENT	(0x1 << 3)
	unsigned long flags;

	char id[ULEN + 1];

	kref ref;
	FlowHead *owner;
	list_head list;

	timespec start;
	event life_event;
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
	FlowDesc *flow = (FlowDesc *)arg;

	while (!kref_put(&flow->ref, __del_flow));
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

int load_flow_manager()
{
	int count = 0, i = 0;
	FlowHead *flows;

	for (DevDesc *desc = dev_head.next;
	     desc != &dev_head; desc = desc->next) {
		count++;
	}
	flows = (FlowHead *)malloc(sizeof(*flows) * count);
	if (flows == NULL) {
		DUMP_LOG("no memory");
		return -1;
	}
	memset(flows, 0, sizeof(*flows) * count);

	for (DevDesc *desc = dev_head.next;
	     desc != &dev_head; desc = desc->next, i++) {
		FlowHead *flow = flows + i;

		strcpy(flow->host, desc->host);
		INIT_LIST_HEAD(&flow->head);
		INIT_LIST_HEAD(&flow->list);
		spin_lock_init(&flow->lock);

		list_add(&flow->head, &flow_head);
	}

	flow_cache = cache_create("flow_cache", sizeof(FlowDesc),
				  0, NULL, NULL);
	if (flow_cache == NULL) {
		DUMP_LOG("no memory");
		return -1;
	}

	return 0;
}

static inline FlowHead* get_flow_head(const char *host)
{
	FlowHead *head = NULL, *pos;

	list_for_each_entry(pos, &flow_head, head) {
		if (!strcmp(pos->host, host)) {
			head = pos;
			break;
		}
	}

	return head;
}

bool new_flow(const char *host, const char *id)
{
	bool res = true;
	FlowDesc *desc;
	FlowHead *head;

	head = get_flow_head(host);
	if (unlikely(head == NULL)) {
		DUMP_LOG("host: %s not register", host);
		res = false;
		goto out;
	}

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
	memcpy(desc->id, id, ULEN);
	if (clock_gettime(CLOCK_MONOTONIC, &desc->start)) {
		cache_free(flow_cache, desc);
		res = false;
		DUMP_LOG("clock_gettime() error");
		goto out;
	}

	spin_lock(&head->lock);
	list_add_tail(&desc->list, &head->list);
	spin_unlock(&head->lock);

out:	return res;
}

void del_flow(const char *host, const char *id)
{
	FlowHead *head;
	FlowDesc *pos, *n, *flow = NULL;
	bool active = false, del = false;

	head = get_flow_head(host);
	if (unlikely(head == NULL)) {
		DUMP_LOG("host: %s not register", host);
		return;
	}

	spin_lock(&head->lock);
	list_for_each_entry_safe(pos, n, &head->list, list) {
		if (!strncmp(pos->id, id, ULEN)) {
			flow = pos;
			if (!g_config.watch_allow) {
				list_del(&flow->list);
				del = true;
			} else {
				if (!(flow->flags & FLOW_WATCH)) {
					list_del(&flow->list);
					del = true;
				} else if (!(flow->flags & FLOW_ACTIVE)) {
					kref_get(&flow->ref);
					flow->flags |= FLOW_ACTIVE;
					active = true;
				}
			}

			break;
		}
	}
	spin_unlock(&head->lock);

	if (del) {
		cache_free(flow_cache, flow);
	}
	if (active && (write(notify_fd, &flow, sizeof(flow)) != sizeof(flow))) {
		spin_lock(&head->lock);
		flow->flags &= ~FLOW_ACTIVE;
		spin_unlock(&head->lock);

		kref_put(&flow->ref, __del_flow);
		DUMP_LOG("failed writing notify pipe");
	}
	if (active) {
		kref_put(&flow->ref, __del_flow);
	}
}

bool hit_flow(const char *host, const char *id)
{
	FlowHead *head;
	FlowDesc *pos, *flow = NULL;
	bool watch = false;

	head = get_flow_head(host);
	if (unlikely(head == NULL)) {
		DUMP_LOG("host: %s not register", host);
		return false;
	}

	spin_lock(&head->lock);
	list_for_each_entry(pos, &head->list, list) {
		if (!strncmp(pos->id, id, ULEN)) {
			flow = pos;
			if (!(flow->flags & FLOW_WATCH) &&
			    g_config.watch_allow) {
				flow->flags |= FLOW_WATCH;
				kref_get(&flow->ref);
				watch = true;
			}
			break;
		}
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
