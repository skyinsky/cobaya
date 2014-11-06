#include <stdlib.h>
#include <string.h>
#include <mysql/errmsg.h>
#include "common.h"
#include "config.h"
#include "mysql_wrapper.h"

namespace cobaya {

MysqlWrapper::MysqlWrapper()
{
	memset(this, 0, sizeof(*this));

	mysql_init(&mysql_con);
}

MysqlWrapper::~MysqlWrapper()
{
	mysql_free_result(mysql_res);
	mysql_close(&mysql_con);
}

int MysqlWrapper::Connect()
{
	my_bool autocon = 1;

	if (mysql_options(&mysql_con,
			  MYSQL_SET_CHARSET_NAME,
			  "utf8")) {
		DUMP_LOG(":%s", mysql_error(&mysql_con));
		return -1;
	}
	if (mysql_options(&mysql_con,
			  MYSQL_OPT_RECONNECT,
			  &autocon)) {
		DUMP_LOG(":%s", mysql_error(&mysql_con));
		return -1;
	}
	if (mysql_real_connect(&mysql_con,
			       g_config.mysql_cobaya_ip,
			       g_config.mysql_user,
			       g_config.mysql_passwd,
			       g_config.mysql_db,
			       0, NULL, 0) == NULL) {
		DUMP_LOG("%s", mysql_error(&mysql_con));
		return -1;
	}

	return 0;
}

int MysqlWrapper::SelectQuery(const char *sql)
{
	int res;

	res = mysql_real_query(&mysql_con, sql, strlen(sql));

	if (res == CR_SERVER_GONE_ERROR || res == CR_SERVER_LOST) {
		goto retry;
	} else if (res != 0) {
		DUMP_LOG("%s", mysql_error(&mysql_con));
		return -1;
	}

ok:
	/* release last time result */
	mysql_free_result(mysql_res);

	mysql_res = mysql_store_result(&mysql_con);
	if (!mysql_res) {
		DUMP_LOG("%s", mysql_error(&mysql_con));
		return -1;
	}
	return 0;

retry:
	if (Connect()) {
		DUMP_LOG("reconnect to mysql error: %s",
			 mysql_error(&mysql_con));
		return -1;
	}
	if (mysql_real_query(&mysql_con, sql, strlen(sql))) {
		DUMP_LOG("%s", mysql_error(&mysql_con));
		return -1;
	}
	goto ok;
}

int MysqlWrapper::ModifyQuery(const char *sql)
{
	int res;

	res = mysql_real_query(&mysql_con, sql, strlen(sql));

	if (res == CR_SERVER_GONE_ERROR || res == CR_SERVER_LOST) {
		goto retry;
	} else if (res != 0) {
		DUMP_LOG("%s", mysql_error(&mysql_con));
	}

	return (res != 0 ? -1 : 0);

retry:
	if (Connect()) {
		DUMP_LOG("reconnect to mysql error: %s",
			 mysql_error(&mysql_con));
		return -1;
	}
	if (mysql_real_query(&mysql_con, sql, strlen(sql))) {
		DUMP_LOG("%s", mysql_error(&mysql_con));
		return -1;
	}
	return 0;
}

} // namespace cobaya
