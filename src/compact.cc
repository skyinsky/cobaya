#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <event.h>
#include "common.h"
#include "keepalive.h"
#include "timer.h"
#include "dev.h"
#include "config.h"
#include "mysql_wrapper.h"
#include "main.h"
#include "flow.h"

namespace cobaya {

timespec old_flow;

static Timer mysql_timer;
static Timer flow_timer;
static Timer start_flow;

static inline void erase_log_table()
{
	const char *sql = "TRUNCATE TABLE 日志";

	if (main_mysql.ModifyQuery(sql)) {
		DUMP_LOG("truncate table error");
	}
}

static inline void erase_exception_table()
{
	const char *sql = "TRUNCATE TABLE 异常";

	if (main_mysql.ModifyQuery(sql)) {
		DUMP_LOG("truncate table error");
	}
}

static void handle_compact_mysql(void *arg)
{
	DUMP_LOG("truncate tables %d days already past",
		 g_config.compact_mysql);

	erase_log_table();
	erase_exception_table();
}

static void handle_compact_flow(void *arg)
{
	remove_expire_flow();

	/* new start flow time point */
	if (clock_gettime(CLOCK_MONOTONIC, &old_flow)) {
		DUMP_LOG("clock_gettime() error");
		exit(EXIT_FAILURE);
	}
}

static void handle_start_flow(void *arg)
{
	uint64_t ms;

	ms = g_config.compact_flow * 24 * 60 * 60 * 1000;
	flow_timer.Set(main_base, ms, handle_compact_flow, NULL);

	if (Timer::SchedPersist(&flow_timer)) {
		DUMP_LOG("sched timer error");
		exit(EXIT_FAILURE);
	}	
	if (clock_gettime(CLOCK_MONOTONIC, &old_flow)) {
		DUMP_LOG("clock_gettime() error");
		exit(EXIT_FAILURE);
	}
}

int load_compaction()
{
	int hour;
	uint64_t ms;
	struct tm *date;
	struct timeval now;

	if (!g_config.compact_allow) {
		return 0;
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

	hour = 24 - date->tm_hour;
	ms = hour * 60 * 60 * 1000;
	start_flow.Set(main_base, ms, handle_start_flow, NULL);

	if (Timer::SchedOneshot(&start_flow)) {
		DUMP_LOG("sched timer error");
		return -1;
	}

	ms = g_config.compact_mysql * 24 * 60 * 60 * 1000;
	mysql_timer.Set(main_base, ms, handle_compact_mysql, NULL);

	if (Timer::SchedPersist(&mysql_timer)) {
		DUMP_LOG("sched timer error");
		return -1;
	}

	return 0;
}

} // namespace cobaya
