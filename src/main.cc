#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <event.h>
#include "mysql_wrapper.h"
#include "common.h"
#include "config.h"
#include "rpc.h"
#include "dev.h"
#include "office.h"
#include "flow.h"
#include "keepalive.h"
#include "compact.h"
#include "main.h"
#include "office_ctl.h"
#include "sensor_server.h"

namespace cobaya {

event_base *main_base;
MysqlWrapper *main_mysql;

} // namespace cobaya

using namespace cobaya;

static void sig_handler(const int sig)
{
	DUMP_LOG("SIGINT handled");
	exit(EXIT_SUCCESS);
}

static int load_main_context()
{
	/* init event base */
	main_base = event_base_new();
	if (main_base == NULL) {
		DUMP_LOG("new event base error");
		return -1;
	}

	/* init mysql for main thread */
	main_mysql = new MysqlWrapper();
	if (main_mysql == NULL) {
		DUMP_LOG("no memory");
		return -1;
	}
	if (main_mysql->Connect()) {
		DUMP_LOG("connect mysql error");
		return -1;
	}
	mysql = main_mysql;

	return 0;
}

int main(int argc, char *argv[])
{
	/* handle SIGINT */
	signal(SIGINT, sig_handler);

	if (load_config("cobaya.ini")) {
		DUMP_LOG("init config error");
		return -1;
	}
	if (load_log_manager()) {
		DUMP_LOG("load log manager error");
		return -1;
	}
	if (load_main_context()) {
		DUMP_LOG("load main thread context error");
		return -1;
	}
	if (load_dev_list()) {
		DUMP_LOG("load dev error");
		return -1;
	}
	if (load_office_list()) {
		DUMP_LOG("load office error");
		return -1;
	}
	if (load_officectl_list()) {
		DUMP_LOG("load office control error");
		return -1;
	}
	if (load_flow_manager()) {
		DUMP_LOG("load flow manager error");
		return -1;
	}
	if (start_rpc_server()) {
		DUMP_LOG("start rpc error");
		return -1;
	}
	if (start_sensor_server()) {
		DUMP_LOG("start sensor server error");
		return -1;
	}
	if (load_compaction()) {
		DUMP_LOG("load compaction error");
		return -1;
	}
	if (load_keepalive()) {
		DUMP_LOG("load keepalive error");
		return -1;
	}

	event_base_loop(main_base, 0);

	stop_rpc_server();

	return 0;
}
