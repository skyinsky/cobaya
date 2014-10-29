#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <libtoolkit/list.h>
#include <libtoolkit/rwlock.h>

#include "common.h"
#include "dev.h"
#include "cache.h"

namespace cobaya {

struct FlowDesc {
	list_head list;

	uint32_t unique_num;
	char host[DEV_HOST];
};

static rwlock_t flow_lock;
static list_head flow_list;
static cache_t *flow_cache;

int load_flow_manager()
{
	rwlock_init(&flow_lock);
	INIT_LIST_HEAD(&flow_list);

	flow_cache = cache_create("flow_cache", sizeof(FlowDesc),
				  0, NULL, NULL);
	if (flow_cache == NULL) {
		DUMP_LOG("no memory");
		return -1;
	}

	return 0;
}

bool new_flow(const char *host, uint32_t num)
{
	bool res = true;
	FlowDesc *desc;

	desc = (FlowDesc *)cache_alloc(flow_cache);
	if (desc == NULL) {
		DUMP_LOG("no memory");
		res = false;
		goto out;
	}
	memset(desc, 0, sizeof(*desc));

	INIT_LIST_HEAD(&desc->list);
	desc->unique_num = num;
	strcpy(desc->host, host);

	write_lock(&flow_lock);
	list_add_tail(&desc->list, &flow_list);
	write_unlock(&flow_lock);

out:	return res;
}

void del_flow(uint32_t num)
{
	FlowDesc *pos, *n;
	DEFINE_LIST_HEAD(remove);

	write_lock(&flow_lock);
	list_for_each_entry_safe(pos, n, &flow_list, list) {
		if (pos->unique_num == num) {
			list_move_tail(&pos->list, &remove);
		}
	}
	write_unlock(&flow_lock);

	list_for_each_entry_safe(pos, n, &remove, list) {
		list_del(&pos->list);
		cache_free(flow_cache, pos);
	}
}

bool hit_flow(const char *host)
{
	bool res = false;
	FlowDesc *desc;

	read_lock(&flow_lock);
	list_for_each_entry(desc, &flow_list, list) {
		if (!strcmp(desc->host, host)) {
			res = true;
			break;
		}
	}
	read_unlock(&flow_lock);

	return res;
}

} // namespace cobaya
