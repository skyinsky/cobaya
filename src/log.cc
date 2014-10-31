#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "common.h"
#include "config.h"

namespace cobaya {

/* stdout */
static int logfd = 1;

int load_log_manager()
{
	int fd;
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char tmp[512] = {0};

	if (gettimeofday(&now, NULL)) {
		DUMP_LOG("gettimeofday() error");
		return -1;
	}
	date = localtime(&now.tv_sec);
	if (date == NULL) {
		DUMP_LOG("localtime() error");
		return -1;
	}
	strftime(datetmp, 128, "%F_%T", date);

	sprintf(tmp, "%s/%s", g_config.dir, datetmp);

	if ((fd = open(tmp, O_CREAT | O_APPEND | O_RDWR, 0644)) == -1) {
		DUMP_LOG("open %s error", tmp);
		return -1;
	}
	logfd = fd;

	return 0;
}

static inline void log_helper(const char *fmt, va_list args)
{
	char buf[1024];
	int len = 0;

	if (fmt != NULL)
		len = vsnprintf(buf, sizeof(buf), fmt, args);

	if (write(logfd, buf, len) != len) {
		perror("write log file error");
	}
}

void log_msg(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	log_helper(fmt, args);
	va_end(args);
}

} // namespace cobaya
