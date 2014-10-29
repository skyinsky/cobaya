#ifndef _MAIN_H
#define _MAIN_H

#include <event.h>
#include "mysql_wrapper.h"

namespace cobaya {

extern bool g_start_monitor;
extern event_base *main_base;
extern MysqlWrapper main_mysql;

} // namespace cobaya

#endif /* _MAIN_H */
