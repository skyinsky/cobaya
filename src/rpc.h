#ifndef _RPC_H
#define _RPC_H

namespace cobaya {

class MysqlWrapper;

/* rpc worker's connection */
extern __thread int notify_fd;
extern __thread MysqlWrapper *mysql;

int  start_rpc_server();
void stop_rpc_server();

} // namespace cobaya

#endif /* _RPC_H */
