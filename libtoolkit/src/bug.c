#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "bug.h"

static exit_callback exit_fn = NULL;
static log_callback log_fn = NULL;

void set_exit_callback(exit_callback cb)
{
	exit_fn = cb;
}

void set_log_callback(log_callback cb)
{
	log_fn = cb;
}

#define log_exit(code)			\
do {					\
	if (exit_fn)			\
		exit_fn(code);		\
	else				\
		exit(EXIT_FAILURE);	\
} while (0)

static void log_helper(int level, const char *errstr, const char *fmt, va_list args)
{
	char buf[1024];
	size_t len;

	if (fmt != NULL)
		vsnprintf(buf, sizeof(buf), fmt, args);
	else
		buf[0] = '\0';

	if (errstr) {
		len = strlen(buf);
		if (len < sizeof(buf) - 3) {
			snprintf(buf + len, sizeof(buf) - len, ": %s", errstr);
		}
	}

	if (log_fn)
		log_fn(level, buf);
	else {
		const char *level_str;
		switch (level) {
		case _LOG_DEBUG:
			level_str = "debug";
			break;
		case _LOG_MSG:
			level_str = "msg";
			break;
		case _LOG_WARN:
			level_str = "warn";
			break;
		case _LOG_ERR:
			level_str = "err";
			break;
		default:
			level_str = "???";
			break;
		}
		(void)fprintf(stderr, "[%s] %s\n", level_str, buf);
	}
}

void log_err(int eval, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	log_helper(_LOG_ERR, strerror(errno), fmt, args);
	va_end(args);
	log_exit(eval);
}

void log_warn(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	log_helper(_LOG_WARN, strerror(errno), fmt, args);
	va_end(args);
}

void log_errx(int eval, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	log_helper(_LOG_ERR, NULL, fmt, args);
	va_end(args);
	log_exit(eval);
}

void log_msgx(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	log_helper(_LOG_MSG, NULL, fmt, args);
	va_end(args);
}

void log_warnx(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	log_helper(_LOG_WARN, NULL, fmt, args);
	va_end(args);
}

#ifdef CONFIG_DEBUG
void _log_debugx(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	log_helper(_LOG_DEBUG, NULL, fmt, args);
	va_end(args);
}
#endif
