#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <libtoolkit/list.h>
#include <libtoolkit/spinlock.h>

#include "common.h"
#include "dev.h"
#include "cache.h"

namespace cobaya {

#define ULEN	11

using namespace std;

struct FlowDesc {
	list_head list;
	char id[ULEN + 1];
};

struct FlowHead {
	list_head head;
	char host[DEV_HOST];

	list_head list;
	spinlock_t lock;
};

static DEFINE_LIST_HEAD(flow_head);
static cache_t *flow_cache;

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
	INIT_LIST_HEAD(&desc->list);
	memcpy(desc->id, id, ULEN);

	spin_lock(&head->lock);
	list_add_tail(&desc->list, &head->list);
	spin_unlock(&head->lock);

out:	return res;
}

void del_flow(const char *host, const char *id)
{
	FlowHead *head;
	FlowDesc *pos, *n, *flow = NULL;

	head = get_flow_head(host);
	if (unlikely(head == NULL)) {
		DUMP_LOG("host: %s not register", host);
		return;
	}

	spin_lock(&head->lock);
	list_for_each_entry_safe(pos, n, &head->list, list) {
		if (!strncmp(pos->id, id, ULEN)) {
			flow = pos;
			list_del(&pos->list);
			break;
		}
	}
	spin_unlock(&head->lock);

	if (flow != NULL) {
		cache_free(flow_cache, flow);
	}
}

bool hit_flow(const char *host, const char *id)
{
	FlowHead *head;
	FlowDesc *pos;
	bool res = false;

	head = get_flow_head(host);
	if (unlikely(head == NULL)) {
		DUMP_LOG("host: %s not register", host);
		return false;
	}

	spin_lock(&head->lock);
	list_for_each_entry(pos, &head->list, list) {
		if (!strncmp(pos->id, id, ULEN)) {
			res = true;
			break;
		}
	}
	spin_unlock(&head->lock);

	return res;
}

} // namespace cobaya
