#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "dev.h"
#include "config.h"
#include "mysql_wrapper.h"
#include "timer.h"
#include "main.h"

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
		dev->item_code = ITEM_HEAD(dev->code);

		dev->next = dev_head.next;
		dev_head.next = dev;

		dev->timer.Set(main_base, g_config.client_check * 60 * 1000,
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

} // namespace cobaya
