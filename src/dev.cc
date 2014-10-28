#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "dev.h"
#include "config.h"
#include "mysql_wrapper.h"
#include "timer.h"

namespace cobaya {

DevDesc dev_head;

DevDesc* parser_rows(char **row)
{
	DevDesc *desc;

	desc = (DevDesc *)malloc(sizeof(*desc));
	if (desc == NULL) {
		DUMP_LOG("no memory");
		goto out;
	}
	memset(desc, 0, sizeof(*desc));

	strcpy(desc->code, row[0]);
	strcpy(desc->name, row[1]);
	strcpy(desc->endpoint, row[2]);
	strcpy(desc->office, row[3]);

out:	return desc;
}

int load_dev_list()
{
	int err = 0;
	char **row;
	MysqlWrapper con;

	if (con.Connect(g_config.mysql_ip,
			g_config.mysql_user,
			g_config.mysql_passwd,
			g_config.mysql_db)) {
		DUMP_LOG("connect mysql error");
		err = -1;
		goto out;
	}
	if (con.SelectQuery("SELECT * FROM `设备`")) {
		DUMP_LOG("connect mysql error");
		err = -1;
		goto close;
	}

	/* point to self */
	dev_head.next = &dev_head;

	for (; (row = con.FetchRow()) != NULL;) {
		DevDesc *res = NULL;

		if ((res = parser_rows(row)) == NULL) {
			DUMP_LOG("parser mysql row error");
			err = -1;
			goto close;
		}

		res->next = dev_head.next;
		dev_head.next = res;
	}

close:
	con.CloseConnect();
out:
	return err;
}

} // namespace cobaya
