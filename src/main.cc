#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <libtoolkit/daemon.h>
#include "mysql_wrapper.h"
#include "common.h"
#include "config.h"
#include "rpc.h"
#include "dev.h"
#include "office.h"
#include "flow.h"
#include "keepalive.h"

using namespace cobaya;

static void sig_handler(const int sig)
{
	DUMP_LOG("SIGINT handled");
	exit(EXIT_SUCCESS);
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
	if (run_keepalive()) {
		DUMP_LOG("run keepalive error");
		return -1;
	}

	stop_rpc_server();

	return 0;
}
