#include <string.h>
#include <libtoolkit/bug.h>
#include <libtoolkit/bitops.h>
#include "common.h"
#include "rpc.h"
#include "rpc_service.h"
#include "config.h"

namespace cobaya {

using namespace RCF;
using namespace google::protobuf;

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

RpcServer::RpcServer() : impl()
{
	this->flags = 0;
	this->server = NULL;
}

RpcServer::~RpcServer()
{

}

int RpcServer::Init()
{
	int res = 0;

	if (test_and_set_bit(FLAG_INIT, &this->flags))
		return -1;

	try {
		RCF::init();

		this->server = new RcfProtoServer();
		if (this->server == NULL)
			res = -1;
		else
			set_bit(FLAG_SERVER, &this->flags);

		if ((res = BindService())) {
			free(this->server);
			this->server = NULL;
			clear_bit(FLAG_SERVER, &this->flags);
		}

	} catch (const RCF::Exception &e) {
		DUMP_LOG("%s", e.getErrorString().c_str());
		res = -1;
	}

	return res;
}

int RpcServer::AddEndpoint(const char *ip, uint16_t port)
{
	int res = 0;

	if (!test_bit(FLAG_SERVER, &this->flags))
		return -1;

	try {
		EndpointPtr ptr(new TcpEndpoint(ip, port));

		this->server->addEndpoint(*ptr);

	} catch (const RCF::Exception &e) {
		DUMP_LOG("%s", e.getErrorString().c_str());
		res = -1;
	}

	return res;
}

int RpcServer::CreateThreadPool(int workers)
{
	int res = 0;

	if (!test_bit(FLAG_SERVER, &this->flags))
		return -1;
	if (test_and_set_bit(FLAG_THREAD, &this->flags))
		return -1;

	try {
		ThreadPoolPtr ptr(new ThreadPool(workers));

		ptr->setThreadName("cobaya_slave");

		this->server->setThreadPool(ptr);

	} catch (const RCF::Exception &e) {
		DUMP_LOG("%s", e.getErrorString().c_str());
		res = -1;
	}

	return res;
}

int RpcServer::StartServer()
{
	int res = 0;

	if (!test_bit(FLAG_SERVER, &this->flags))
		return -1;

	try {
		this->server->start();

	} catch (const RCF::Exception &e) {
		DUMP_LOG("%s", e.getErrorString().c_str());
		res = -1;
	}

	return res;
}

void RpcServer::StopServer()
{
	if (!test_bit(FLAG_SERVER, &this->flags))
		return;

	try {
		this->server->stop();

	} catch (const RCF::Exception &e) {
		DUMP_LOG("%s", e.getErrorString().c_str());
	}
}

void RpcServer::_exit()
{
	this->flags = 0;
	free(this->server);
}

int RpcServer::BindService()
{
	int res = 0;

	if (!test_bit(FLAG_SERVER, &this->flags))
		return -1;

	try {
		this->server->bindService(this->impl);

	} catch (const RCF::Exception &e) {
		DUMP_LOG("%s", e.getErrorString().c_str());
		res = -1;
	}

	return res;
}

static RpcServer g_server;

int start_rpc_server()
{
	if (g_server.Init()) {
		DUMP_LOG("init rpc error");
		return -1;
	}
	if (g_server.AddEndpoint(g_config.rpc_ip,
				 g_config.rpc_port)) {
		DUMP_LOG("listen %s:%d error",
			 g_config.rpc_ip, g_config.rpc_port);
		return -1;
	}
	if (g_server.CreateThreadPool(g_config.worker)) {
		DUMP_LOG("create slaves error");
		return -1;
	}
	if (g_server.StartServer()) {
		DUMP_LOG("start rpc error");
		return -1;
	}

	return 0;
}

void stop_rpc_server()
{
	g_server.StopServer();
}

} // namespace cobaya
