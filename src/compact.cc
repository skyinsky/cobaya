#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <event.h>
#include "common.h"
#include "keepalive.h"
#include "timer.h"
#include "dev.h"
#include "config.h"
#include "mysql_wrapper.h"
#include "main.h"

namespace cobaya {

static Timer compact_timer;

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

static void handle_compact(void *arg)
{
	erase_log_table();
	erase_exception_table();
}

int load_compaction()
{
	uint64_t ms;

	if (!g_config.compact_allow) {
		return 0;
	}

	ms = g_config.compact_interval * 24 * 60 * 60 * 1000;
	compact_timer.Set(main_base, ms, handle_compact, NULL);

	if (Timer::SchedPersist(&compact_timer)) {
		DUMP_LOG("sched timer error");
		return -1;
	}

	return 0;
}

} // namespace cobaya
