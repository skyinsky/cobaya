#ifndef _MAIN_H
#define _MAIN_H

#include <event.h>

namespace cobaya {

class MysqlWrapper;

extern event_base *main_base;
extern MysqlWrapper *main_mysql;

} // namespace cobaya

#endif /* _MAIN_H */
