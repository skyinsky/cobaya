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
	bool is_watch;

	list_head list;

	timespec start;

	uint64_t user_id;
	uint32_t office_id;
	char apply_id[APPLY_ID];
	char user[USER_NAME];
	char doctor[USER_NAME];

	int valid;
	ItemDesc *items[ITEM_CHILD];
};

static cache_t *flow_cache;
static DEFINE_LIST_HEAD(flow_head);

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

static inline ItemDesc* head_search(OfficeCtl *office, const char *item_name)
{
	for (ItemDesc *item = office->list_head.next;
	     item != &office->list_head; item = item->next) {
		if (!strcmp(item_name, item->name)) {
			return item;
		}
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
		//*item = head_search(&office->tree, his->item_id);
		*item = head_search(office, his->item_name);
		if (*item != NULL) {
			head = (FlowHead *)office->head[(*item)->code];
		} else {
//			DUMP_LOG("[cobaya.监控科室] %s:%s 不存在执行项目%d",
//				 office->strid, office->name, his->item_id);
			DUMP_LOG("[cobaya.监控科室] %s:%s 不存在执行项目%s",
				 office->strid, office->name, his->item_name);
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

		list_del(&flow->list);

		break;
	}
	spin_unlock(&head->lock);

	cache_free(flow_cache, flow);
}

void del_flow(void *_head, uint64_t user_id)
{
	FlowHead *head = (FlowHead *)_head;
	FlowDesc *pos, *n, *flow = NULL;

	spin_lock(&head->lock);
	list_for_each_entry_safe(pos, n, &head->list, list) {
		if (pos->user_id != user_id) {
			continue;
		}
		flow = pos;
		list_del(&flow->list);

		break;
	}
	spin_unlock(&head->lock);

	if (flow != NULL) {
		cache_free(flow_cache, flow);
	}
}

bool hit_flow(void *_head, uint64_t user_id)
{
	FlowHead *head = (FlowHead *)_head;
	FlowDesc *pos, *flow = NULL;

	spin_lock(&head->lock);
	list_for_each_entry(pos, &head->list, list) {
		if (pos->user_id != user_id)
			continue;
		flow = pos;
		flow->is_watch = true;
		break;
	}
	spin_unlock(&head->lock);

	return (flow != NULL);
}

void get_flow(void *_head, MsgFetchFlowRsp *rsp)
{
	FlowDesc *pos;
	FlowHead *head = (FlowHead *)_head;

	spin_lock(&head->lock);
	list_for_each_entry(pos, &head->list, list) {
		if (pos->is_watch) {
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
