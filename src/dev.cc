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
		strcpy(dev->code, row[0]);
		strcpy(dev->name, row[1]);
		strcpy(dev->host, row[2]);
		strcpy(dev->office, row[3]);

		dev->next = dev_head.next;
		dev_head.next = dev;
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
