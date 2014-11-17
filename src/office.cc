#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "config.h"
#include "office.h"
#include "mysql_wrapper.h"
#include "main.h"

namespace cobaya {

OfficeDesc *offices;

static OfficeDesc* parser_rows(int i, char **row)
{
	OfficeDesc *desc = &offices[i];

	desc->id = atoi(row[0]);
	strcpy(desc->name, row[1]);

	if (desc->id != (uint32_t)i) {
		DUMP_LOG("office (%s:%s) not sequence",
			 row[0], row[1]);
		desc = NULL;
	}
	
	return desc;
}

int load_office_list()
{
	int err = 0, rows;
	char **row;

	if (main_mysql->SelectQuery("SELECT * FROM `科室`")) {
		DUMP_LOG("connect mysql error");
		err = -1;
		goto out;
	}

	rows = main_mysql->GetNumRows();
	offices = (OfficeDesc *)calloc(rows, sizeof(OfficeDesc));
	if (offices ==  NULL) {
		DUMP_LOG("no memory");
		err = -1;
		goto out;
	}
	
	for (int i = 0; (row = main_mysql->FetchRow()) != NULL; i++) {
		OfficeDesc *res = NULL;

		if ((res = parser_rows(i, row)) == NULL) {
			DUMP_LOG("parser mysql row error");
			err = -1;
			goto out;
		}
	}

out:
	return err;
}

} // namespace cobaya
