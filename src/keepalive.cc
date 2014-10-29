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

namespace cobaya {

static event_base *g_base;
static MysqlWrapper g_mysql;

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

	sprintf(tmp, "INSERT INTO `异常` VALUES ('%s', '%s', '%s', '%s', '%s')",
		dev->code, dev->name, dev->host, dev->office, datetmp);
	if (g_mysql.ModifyQuery(tmp)) {
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
	dev->timer.Set(g_base, g_config.client_timeout * 1000,
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

int run_keepalive()
{
	int err = 0;

	/* init event base */
	g_base = event_base_new();
	if (g_base == NULL) {
		DUMP_LOG("new event base error");
		err = -1;
		goto err;
	}

	/* init mysql conn */
	if (g_mysql.Connect(g_config.mysql_ip,
			    g_config.mysql_user,
			    g_config.mysql_passwd,
			    g_config.mysql_db)) {
		DUMP_LOG("connect mysql error");
		err = -1;
		goto close_base;
	}

	/* init dev timer */
	for (DevDesc *desc = dev_head.next;
	     desc != &dev_head; desc = desc->next) {
		if (init_dev_timer(desc)) {
			DUMP_LOG("init dev timer error");
			err = -1;
			goto err;
		}
	}

	return event_base_loop(g_base, 0);

close_base:
	event_base_free(g_base);
err:	
	return err;
}

} // namespace cobaya
