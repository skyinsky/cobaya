#ifndef _LOG_H
#define _LOG_H

namespace cobaya {

int load_log_manager();
void log_msg(const char *fmt, ...);

} // namespace cobaya

#endif /* _LOG_H */
