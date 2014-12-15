#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "main.h"
#include "mysql_wrapper.h"
#include "office_ctl.h"

namespace cobaya {

OfficeCtl officectl_head;

static int get_officectl_items(char *office_id, char *item_code)
{
	int rows = -1;
	char sql[512] = {0};

	sprintf(sql, "SELECT * FROM `项目` WHERE "
		"`项目编码`='%s' AND `执行科室编号`='%s'",
		item_code, office_id);

	if (main_mysql->SelectQuery(sql)) {
		DUMP_LOG("connect mysql error");
		goto out;
	}
	rows = main_mysql->GetNumRows();

out:
	return rows;
}

static int check_officectl_itmes()
{
	int err = 0;

	for (OfficeCtl *office = officectl_head.next;
	     office != &officectl_head; office = office->next) {
		char *p = office->items;
		char *end = office->items + OFFICE_ITEM;

		for (; p < end; p++) {
			int code, items;
			char *item_code;

			if (*p != '_') {
				continue;
			} else {
				p++;
			}

			code = ITEM_HEAD(p);
			item_code = HEAD_ITEM(code);

			items = get_officectl_items(office->strid, item_code);
#ifdef COBAYA_DEBUG
			DUMP_LOG("科室 (%s:%s) 需执行项目(%s:%d)",
				 office->strid, office->name,
				 item_code, items);
#endif
			if (items == -1 || items > ITEM_CHILD) {
				DUMP_LOG("科室 (%s:%s) 执行项目(%s:%d)太多",
					 office->strid, office->name,
					 item_code, items);
				err = -1;
				goto out;
			}
		}
	}

out:
	return err;
}

static bool insert_item(rb_root *root, ItemDesc *data)
{
	rb_node **n = &(root->rb_node), *parent = NULL;

  	/* Figure out where to put new node */
  	while (*n) {
  		ItemDesc *item = container_of(*n, ItemDesc, node);
		int res = data->id - item->id;

		parent = *n;
  		if (res < 0)
  			n = &((*n)->rb_left);
  		else if (res > 0)
  			n = &((*n)->rb_right);
  		else
  			return false;
  	}

  	/* Add new node and rebalance tree. */
  	rb_link_node(&data->node, parent, n);
  	rb_insert_color(&data->node, root);

	return true;
}

static int load_office_ctl(OfficeCtl *office)
{
	int err = 0, rows;
	char **row;
	char sql[512] = {0};
	ItemDesc *items = NULL;

	sprintf(sql, "SELECT * FROM `项目` WHERE `执行科室编号`='%s'",
		office->strid);

	if (main_mysql->SelectQuery(sql)) {
		DUMP_LOG("connect mysql error");
		err = -1;
		goto out;
	}
	if (main_mysql->GetNumFields() < 5) {
		DUMP_LOG("[cobaya.项目] 表字段错误");
		err = -1;
		goto out;
	}

	rows = main_mysql->GetNumRows();
	items = (ItemDesc *)calloc(rows, sizeof(ItemDesc));
	if (items ==  NULL) {
		DUMP_LOG("no memory");
		err = -1;
		goto out;
	}

#ifdef COBAYA_DEBUG
	DUMP_LOG("监控科室: %s : %s : %s : %s",
		 office->strid, office->name,
		 office->owner, office->items);
#endif

	for (ItemDesc *item = &items[0];
	     (row = main_mysql->FetchRow()) != NULL; item++) {
		if (strlen(row[2]) >= ITEM_NAME) {
			DUMP_LOG("添加项目 (%s:%s) len=%d 名称太长",
				 row[2], row[1], strlen(row[2]));
			err = -1;
			goto out;
		}
		item->id = atoi(row[1]);
		item->code = ITEM_HEAD(row[3]);
		strcpy(item->name, row[2]);

#ifdef COBAYA_DEBUG
	DUMP_LOG("执行项目: %s", item->name);
#endif

		if (!insert_item(&office->tree, item)) {
			DUMP_LOG("添加项目 (%s:%s) 失败",
				 row[2], row[1]);
			err = -1;
			goto out;
		}
		item->next = office->list_head.next;
		office->list_head.next = item;
	}

out:
	return err;
}

int load_officectl_list()
{
	int err = 0, rows;
	char **row;
	OfficeCtl *offices;

	if (main_mysql->SelectQuery("SELECT * FROM `监控科室`")) {
		DUMP_LOG("connect mysql error");
		err = -1;
		goto out;
	}

	rows = main_mysql->GetNumRows();
	offices = (OfficeCtl *)calloc(rows, sizeof(OfficeCtl));
	if (offices ==  NULL) {
		DUMP_LOG("no memory");
		err = -1;
		goto out;
	}

	/* init officectl list */
	for (int i = 0; i < rows; i++) {
		if (i + 1 == rows)
			break;
		offices[i].next = &offices[i + 1];
	}
	officectl_head.next = &offices[0];
	offices[rows - 1].next = &officectl_head;
	
	for (OfficeCtl *office = &offices[0];
	     (row = main_mysql->FetchRow()) != NULL; office++) {
		if (main_mysql->GetNumFields() < 4) {
			DUMP_LOG("[cobaya.监控科室] 表字段错误");
			err = -1;
			goto out;
		}

		strcpy(office->strid, row[0]);
		strcpy(office->name, row[1]);
		strcpy(office->owner, row[2]);
		strcpy(office->items, row[3]);

		office->id = atoi(row[0]);
		RB_EMPTY_ROOT(&office->tree);
		office->list_head.next = &office->list_head;
	}

	for (OfficeCtl *office = officectl_head.next;
	     office != &officectl_head; office = office->next) {
		if (load_office_ctl(office)) {
			DUMP_LOG("初始化监控科室(%s:%s)失败",
				 office->owner, office->name);
			err = -1;
			goto out;
		}
	}

	if (check_officectl_itmes()) {
		DUMP_LOG("监控科室执行项目校验失败");
		err = -1;
		goto out;
	}

out:
	return err;
}


} // namespace cobaya
