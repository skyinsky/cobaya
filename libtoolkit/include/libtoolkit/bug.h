#ifndef _LIBTOOLKIT_BUG_H
#define _LIBTOOLKIT_BUG_H

#include <stdlib.h>
#include <stdio.h>
#include <libtoolkit/asm/config.h>
#include <libtoolkit/common.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
#define _CHECK_FMT(a,b) __attribute__((format(printf, a, b)))
#else
#define _CHECK_FMT(a,b)
#endif

#define _LOG_DEBUG	0
#define _LOG_ERR	1
#define _LOG_MSG	2	
#define _LOG_WARN	3	

void log_err(int eval, const char *fmt, ...) _CHECK_FMT(2,3);
void log_msg(const char *fmt, ...) _CHECK_FMT(1,2);
void log_warn(const char *fmt, ...) _CHECK_FMT(1,2);

void log_errx(int eval, const char *fmt, ...) _CHECK_FMT(2,3);
void log_msgx(const char *fmt, ...) _CHECK_FMT(1,2);
void log_warnx(const char *fmt, ...) _CHECK_FMT(1,2);

#ifdef CONFIG_DEBUG
void log_debug(const char *fmt, ...) _CHECK_FMT(1,2);
void log_debugx(const char *fmt, ...) _CHECK_FMT(1,2);
#else
#define log_debug(x, ...) do { } while (0)
#define log_debugx(x, ...) do { } while (0)
#endif

/**
 * Don't use BUG() or BUG_ON() unless there's really no way out; one
 * example might be detecting data structure corruption in the middle
 * of an operation that can't be backed out of.  If the (sub)system
 * can somehow continue operating, perhaps with reduced functionality,
 * it's probably not BUG-worthy.
 *
 * If you're tempted to BUG(), think again:  is completely giving up
 * really the *only* solution?  There are usually better options, where
 * users don't need to reboot ASAP and can mostly shut down cleanly.
 */
#define BUG()					\
do { 						\
	log_errx(_LOG_ERR, "%s:%d/%s()!\n",	\
		__FILE__, __LINE__, __func__); 	\
} while (0)

#define BUG_ON(condition) do { if (unlikely(condition)) BUG(); } while(0)

/**
 * Callback function used to intercept internal's log messages.
 * @param level
 * 	refer to _LOG_XXX
 * @param msg
 * 	log msg
 * @see
 * 	set_log_callback
 */
typedef void (*log_callback)(int level, const char *msg);

/** Redirect internal's log messages */
void set_log_callback(log_callback cb);

/**
 * Function to be called when occur a fatal error.
 * @param status
 * 	refer to 'exit()'
 * @see
 * 	set_fatal_callback
 */
typedef void (*exit_callback)(int status);

/**
 * Override the internal fatal behavior.
 *
 * By default, call exit(EXIT_FAILURE) if a error makes it impossible
 * to continue correct operation.  This function allows you to supply
 * another callback instead.
 */
void set_exit_callback(exit_callback cb);

#undef _CHECK_FMT

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_BUG_H */
