#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <libtoolkit/daemon.h>
#include "common.h"
#include "config.h"
#include "monitor.h"

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

	monitor_loop();

	return 0;
}
