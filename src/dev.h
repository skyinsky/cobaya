#ifndef _DEV_H
#define _DEV_H

#include <event.h>
#include "timer.h"

namespace cobaya {

#define DEV_CODE	10
#define DEV_NAME	20
#define DEV_HOST	20
#define DEV_OFFICE	10

struct DevDesc {
	DevDesc *next;
	
	/* timer event */
	timespec client_update;
	timespec event_update;
	Timer timer;

	/* mysql:table, 设备表 */
	char code[DEV_CODE];
	char name[DEV_NAME];
	char host[DEV_HOST];
	char office[DEV_OFFICE];
};

extern DevDesc dev_head;

int load_dev_list();

DevDesc* find_dev_by_host(const char *host);
DevDesc* find_dev_by_code(const char *code);

} // namespace cobaya

#endif /* _DEV_H */
