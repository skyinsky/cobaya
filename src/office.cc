#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "config.h"
#include "office.h"
#include "mysql_wrapper.h"
#include "main.h"

namespace cobaya {

OfficeDesc office_head;

static OfficeDesc* parser_rows(char **row)
{
	OfficeDesc *desc;

	desc = (OfficeDesc *)malloc(sizeof(*desc));
	if (desc == NULL) {
		DUMP_LOG("no memory");
		goto out;
	}
	memset(desc, 0, sizeof(*desc));

	strcpy(desc->name, row[0]);

out:	return desc;
}

int load_office_list()
{
	int err = 0;
	char **row;

	if (main_mysql->SelectQuery("SELECT * FROM `科室`")) {
		DUMP_LOG("connect mysql error");
		err = -1;
		goto out;
	}

	/* point to self */
	office_head.next = &office_head;

	for (; (row = main_mysql->FetchRow()) != NULL;) {
		OfficeDesc *res = NULL;

		if ((res = parser_rows(row)) == NULL) {
			DUMP_LOG("parser mysql row error");
			err = -1;
			goto out;
		}

		res->next = office_head.next;
		office_head.next = res;
	}

out:
	return err;
}

} // namespace cobaya
