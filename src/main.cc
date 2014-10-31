#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <event.h>
#include <libtoolkit/daemon.h>
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

namespace cobaya {

event_base *main_base;
MysqlWrapper main_mysql;

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

	/* init mysql conn */
	if (main_mysql.Connect(g_config.mysql_cobaya_ip,
			       g_config.mysql_user,
			       g_config.mysql_passwd,
			       g_config.mysql_db)) {
		DUMP_LOG("connect mysql error");
		return -1;
	}

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
	if (g_config.daemon && sigignore(SIGHUP)) {
		DUMP_LOG("ignore signal SIGHUP error");
		return -1;
	}
	if (g_config.daemon && daemonize(1, 1)) {
		DUMP_LOG("daemon error");
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
	if (load_flow_manager()) {
		DUMP_LOG("load flow manager error");
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
	if (start_rpc_server()) {
		DUMP_LOG("start rpc error");
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
	DUMP_LOG("fuck");

	event_base_loop(main_base, 0);

	stop_rpc_server();

	return 0;
}
