#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "dev.h"
#include "config.h"
#include "mysql_wrapper.h"
#include "timer.h"
#include "main.h"
#include "rpc.h"

namespace cobaya {

DevDesc dev_head;

static void handle_check_timeout(void *arg)
{
	DevDesc *dev = (DevDesc *)arg;

	dev->check_flow = false;
}

int load_dev_list()
{
	int err = 0, count;
	char **row;
	DevDesc *desc, *dev;

	if (main_mysql->SelectQuery("SELECT * FROM `设备`")) {
		DUMP_LOG("query mysql error");
		err = -1;
		goto out;
	}
	count = main_mysql->GetNumRows();

	/* point to self */
	dev_head.next = &dev_head;

	desc = (DevDesc *)malloc(sizeof(*desc) * count);
	if (desc == NULL) {
		DUMP_LOG("no memory");
		err = -1;
		goto out;
	}
	memset(desc, 0, sizeof(*desc) * count);

	for (dev = desc; (row = main_mysql->FetchRow()) != NULL; dev++) {
		if (main_mysql->GetNumFields() < 4) {
			DUMP_LOG("[cobaya.设备] 表字段错误");
			err = -1;
			goto out;
		}
		if (strlen(row[0]) >= DEV_CODE) {
			DUMP_LOG("字段 (%s) len = %d 太长",
				 row[0], strlen(row[0]));
			err = -1;
			goto out;
		}
		if (strlen(row[1]) >= DEV_NAME) {
			DUMP_LOG("字段 (%s) len = %d 太长",
				 row[1], strlen(row[1]));
			err = -1;
			goto out;
		}
		if (strlen(row[2]) >= DEV_HOST) {
			DUMP_LOG("字段 (%s) len = %d 太长",
				 row[2], strlen(row[2]));
			err = -1;
			goto out;
		}
		if (strlen(row[3]) >= OFFICE_ID) {
			DUMP_LOG("字段 (%s) len = %d 太长",
				 row[3], strlen(row[3]));
			err = -1;
			goto out;
		}
		if (strlen(row[4]) >= OFFICE_NAME) {
			DUMP_LOG("字段 (%s) len = %d 太长",
				 row[4], strlen(row[4]));
			err = -1;
			goto out;
		}
		if (strlen(row[5]) >= OFFICE_OWNER) {
			DUMP_LOG("字段 (%s) len = %d 太长",
				 row[5], strlen(row[5]));
			err = -1;
			goto out;
		}
		strcpy(dev->code, row[0]);
		strcpy(dev->name, row[1]);
		strcpy(dev->host, row[2]);
		strcpy(dev->office_id, row[3]);
		strcpy(dev->office_name, row[4]);
		strcpy(dev->office_owner, row[5]);
		strcpy(dev->doct_name, "AA_匿名");
		dev->item_code = ITEM_HEAD(dev->code);

		dev->next = dev_head.next;
		dev_head.next = dev;

		dev->check_timer.Set(main_base, g_config.client_check * 60 * 1000,
			       handle_check_timeout, dev);
	}

out:
	return err;
}

DevDesc* find_dev_by_host(const char *host)
{
	DevDesc * dev = NULL;

	for (DevDesc *desc = dev_head.next;
	     desc != &dev_head; desc = desc->next) {
		if (!strcmp(desc->host, host)) {
			dev = desc;
			break;
		}
	}

	return dev;
}

DevDesc* find_dev_by_code(const char *code)
{
	DevDesc * dev = NULL;

	for (DevDesc *desc = dev_head.next;
	     desc != &dev_head; desc = desc->next) {
		if (!strcmp(desc->code, code)) {
			dev = desc;
			break;
		}
	}

	return dev;
}

static void store_doubt_flow(DevDesc *dev)
{
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char sql[512] = {0};

	if (gettimeofday(&now, NULL)) {
		DUMP_LOG("gettimeofday() error");
		return;
	}
	date = localtime(&now.tv_sec);
	if (date == NULL) {
		DUMP_LOG("localtime() error");
		return;
	}
	strftime(datetmp, 128, "%F %T", date);

	sprintf(sql, "INSERT INTO `日志` VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
		dev->doct_name, dev->host, datetmp,
		dev->code, dev->name, dev->office_id, dev->office_name, dev->office_owner);
	if (mysql->ModifyQuery(sql)) {
		DUMP_LOG("insert log table (dev_code:%s) error", dev->code);
	}
}

void hit_person_from_sensor(DevDesc *dev)
{
	timespec cur_time;

	if (clock_gettime(CLOCK_MONOTONIC, &dev->client_update)) {
		DUMP_LOG("clock_gettime() error");
		return;
	}
	cur_time = dev->client_update;

	if (!dev->check_flow) {
		store_doubt_flow(dev);
		return;
	}

	if (dev->sensor_last == 0) {
		dev->sensor_last = cur_time.tv_sec;
		return;
	}

	if (cur_time.tv_sec - dev->sensor_last > 60 * g_config.client_sensor) {
		store_doubt_flow(dev);
	}

	dev->sensor_last = cur_time.tv_sec;
}

} // namespace cobaya
