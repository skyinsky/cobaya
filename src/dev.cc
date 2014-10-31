#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "dev.h"
#include "config.h"
#include "mysql_wrapper.h"
#include "timer.h"

namespace cobaya {

DevDesc dev_head;

int load_dev_list()
{
	int err = 0;
	char **row;
	MysqlWrapper con;
	DevDesc *desc, *dev;

	if (con.Connect(g_config.mysql_cobaya_ip,
			g_config.mysql_user,
			g_config.mysql_passwd,
			g_config.mysql_db)) {
		DUMP_LOG("connect mysql error");
		err = -1;
		goto out;
	}
	if (con.SelectQuery("SELECT * FROM `设备`")) {
		DUMP_LOG("query mysql error");
		err = -1;
		goto close;
	}

	/* point to self */
	dev_head.next = &dev_head;

	desc = (DevDesc *)malloc(sizeof(*desc) * con.m_iFields);
	if (desc == NULL) {
		DUMP_LOG("no memory");
		err = -1;
		goto close;
	}
	memset(desc, 0, sizeof(*desc) * con.m_iFields);

	for (dev = desc; (row = con.FetchRow()) != NULL; dev++) {
		strcpy(dev->code, row[0]);
		strcpy(dev->name, row[1]);
		strcpy(dev->host, row[2]);
		strcpy(dev->office, row[3]);

		dev->next = dev_head.next;
		dev_head.next = dev;
	}

close:
	con.CloseConnect();
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
