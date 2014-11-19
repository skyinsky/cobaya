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

static void store_timeout_exception(DevDesc *dev)
{
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char tmp[512] = {0};

	if (gettimeofday(&now, NULL)) {
		DUMP_LOG("gettimeofday() error");
		return;
	}

	date = localtime(&now.tv_sec);
	if (date == NULL) {
		DUMP_LOG("localtime() error");
		return;
	}
	strftime(datetmp, 128, "%F %T", date);

	sprintf(tmp, "INSERT INTO `异常` VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s')",
		dev->code, dev->name, dev->host,
		dev->office_id, dev->office_name, dev->office_owner, datetmp);
	if (main_mysql->ModifyQuery(tmp)) {
		DUMP_LOG("insert value error");
	}
}

static void handle_dev_timeout(void *arg)
{
	DevDesc *dev = (DevDesc *)arg;

	if (dev->client_update.tv_sec < dev->event_update.tv_sec) {
		store_timeout_exception(dev);
	}

	/* update alive heartbeat */
	if (clock_gettime(CLOCK_MONOTONIC, &dev->event_update)) {
		DUMP_LOG("clock_gettime() error");
	}
}

static int init_dev_timer(DevDesc *dev)
{
	dev->timer.Set(main_base, g_config.client_timeout * 1000,
		       handle_dev_timeout, dev);

	if (Timer::SchedPersist(&dev->timer)) {
		DUMP_LOG("sched timer error");
		return -1;
	}
	if (clock_gettime(CLOCK_MONOTONIC, &dev->event_update)) {
		DUMP_LOG("clock_gettime() error");
		return -1;
	}

	return 0;
}

int load_keepalive()
{
	/* init dev timer */
	for (DevDesc *desc = dev_head.next;
	     desc != &dev_head; desc = desc->next) {
		if (init_dev_timer(desc)) {
			DUMP_LOG("init dev timer error");
			return -1;
		}
	}

	return 0;
}

} // namespace cobaya
