#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

static int set_work_dir()
{
	int len;
	char *p;
	char exe[1024] = {0};
	char path[1024] = {0};

	len = readlink("/proc/self/exe", exe, 1024);
	if (len < 0 || len >= 1024) {
		DUMP_LOG("readlink() error");
		return -1;
	}

	p = exe + strlen(exe);
	while (*--p != '/');
	memcpy(path, exe, p - exe);

	if (chdir(path) == -1) {
		perror("chdir");
		DUMP_LOG("chdir(%s) error", path);
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	/* handle SIGINT */
	signal(SIGINT, sig_handler);

	if (set_work_dir()) {
		DUMP_LOG("set work dir error");
		return -1;
	}
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
