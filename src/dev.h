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

	/* 当前登录医生 */
	char doct_name[USER_NAME];

	/* FlowHead */
	void *head;

	/* 机器正在作检查 */
	bool check_flow;	// 标示设备开启允许检查病人流程
	Timer check_timer;
	time_t sensor_last;
};

extern DevDesc dev_head;

int load_dev_list();

DevDesc* find_dev_by_host(const char *host);
DevDesc* find_dev_by_code(const char *code);

void hit_person_from_sensor(DevDesc *dev);

} // namespace cobaya

#endif /* _DEV_H */
