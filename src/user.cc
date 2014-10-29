#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "common.h"
#include "config.h"
#include "dev.h"
#include "rpc.h"
#include "mysql_wrapper.h"

namespace cobaya {

/* 
 *  1 : exist
 *  0 : not exist
 * -1 : error
 */
static inline int user_exist(const char *user)
{
	char sql[512] = {0};

	sprintf(sql, "SELECT `姓名` FROM `用户` WHERE `姓名` = '%s'", user);

	if (mysql->SelectQuery(sql)) {
		DUMP_LOG("query mysql error");
		return -1;
	}
	return mysql->m_iFields;
}

/* 
 *  1 : exist
 *  0 : not exist
 * -1 : error
 */
static inline int user_exist(const char *user, const char *passwd)
{
	char sql[512] = {0};

	sprintf(sql, "SELECT `姓名` FROM `用户` WHERE `姓名` = '%s' AND `密码` = '%s'",
		user, passwd);

	if (mysql->SelectQuery(sql)) {
		DUMP_LOG("query mysql error");
		return -1;
	}
	return mysql->m_iFields;
}

int logon_client(const char *user, const char *passwd, const char *host)
{
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char tmp[512] = {0};

	if (user_exist(user, passwd) != 1) {
		return -1;
	}

	if (gettimeofday(&now, NULL)) {
		DUMP_LOG("gettimeofday() error");
		return -1;
	}

	date = localtime(&now.tv_sec);
	if (date == NULL) {
		DUMP_LOG("localtime() error");
		return -1;
	}
	strftime(datetmp, 128, "%F %T", date);

	sprintf(tmp, "UPDATE `用户` "
		"SET `登录终端`='%s', `登录时间`='%s'"
		"WHERE `姓名`='%s'",
		host, datetmp, user);
	if (mysql->ModifyQuery(tmp)) {
		DUMP_LOG("update user:%s error", user);
		return -1;
	}

	return 0;
}

int logout_client(const char *user)
{
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char tmp[512] = {0};

	if (user_exist(user) != 1) {
		return -1;
	}

	if (gettimeofday(&now, NULL)) {
		DUMP_LOG("gettimeofday() error");
		return -1;
	}

	date = localtime(&now.tv_sec);
	if (date == NULL) {
		DUMP_LOG("localtime() error");
		return -1;
	}
	strftime(datetmp, 128, "%F %T", date);

	sprintf(tmp, "UPDATE `用户` "
		"SET `登录时间`='%s' WHERE `姓名`='%s'",
		datetmp, user);
	if (mysql->ModifyQuery(tmp)) {
		DUMP_LOG("update user:%s error", user);
		return -1;
	}

	return 0;
}

int update_user(const char *user, const char *passwd, const char *host)
{
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char tmp[512] = {0};

	if (user_exist(user) != 1) {
		return -1;
	}

	if (gettimeofday(&now, NULL)) {
		DUMP_LOG("gettimeofday() error");
		return -1;
	}

	date = localtime(&now.tv_sec);
	if (date == NULL) {
		DUMP_LOG("localtime() error");
		return -1;
	}
	strftime(datetmp, 128, "%F %T", date);

	sprintf(tmp, "UPDATE `用户` "
		"SET `密码`='%s' , `登录终端`='%s', `登录时间`='%s'"
		"WHERE `姓名`='%s'",
		passwd, host, datetmp, user);
	if (mysql->ModifyQuery(tmp)) {
		DUMP_LOG("update user:%s error", user);
		return -1;
	}

	return 0;
}

} // namespace cobaya








