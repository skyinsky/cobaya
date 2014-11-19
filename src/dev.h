#ifndef _DEV_H
#define _DEV_H

#include <event.h>
#include "timer.h"
#include "common.h"

namespace cobaya {

struct DevDesc {
	DevDesc *next;
	
	/* timer event */
	timespec client_update;
	timespec event_update;
	Timer timer;

	/* mysql:table, 设备表 */
	int item_code;
	char code[DEV_CODE];
	char name[DEV_NAME];
	char host[DEV_HOST];
	char office_id[OFFICE_ID];
	char office_name[OFFICE_NAME];
	char office_owner[OFFICE_OWNER];

	/* FlowHead */
	void *head;
};

extern DevDesc dev_head;

int load_dev_list();

DevDesc* find_dev_by_host(const char *host);
DevDesc* find_dev_by_code(const char *code);

} // namespace cobaya

#endif /* _DEV_H */
