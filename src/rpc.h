#ifndef _RPC_H
#define _RPC_H

#include <libtoolkit/bitops.h>
#include <librcfproto/RCFProto.hpp>
#include "rpc_service.h"

namespace cobaya {

using namespace RCF;
	
class RpcServer {
public:
	RpcServer();
	~RpcServer();

	/* init RCF library & create RcfProtoServer object */
	int Init();

	/* Configuring server endpoints */
	int AddEndpoint(const char *ip, uint16_t port);

	/* Configuring server-side threading */
	int CreateThreadPool(int workers);

	int StartServer();
	void StopServer();

protected:
	/* bind protobuf service */
	int BindService();

	/* free RcfProtoServer object */
	void _exit();

private:
#define FLAG_INIT	(0x1 << 0)
#define FLAG_SERVER	(0x1 << 1)
#define FLAG_THREAD	(0x1 << 2)
	unsigned long flags;

	RcfProtoServer *server;

	/* define rpc service implimentation */
	RpcServiceImpl impl;
};

} // namespace cobaya

#endif /* _RPC_H */
