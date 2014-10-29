#ifndef _RPC_H
#define _RPC_H

#include "mysql_wrapper.h"

namespace cobaya {

/* rpc worker's connection */
extern __thread MysqlWrapper *mysql;

int  start_rpc_server();
void stop_rpc_server();

} // namespace cobaya

#endif /* _RPC_H */
