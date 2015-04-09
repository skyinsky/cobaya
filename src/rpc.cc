#include <string.h>
#include <pthread.h>
#include <libtoolkit/bug.h>
#include <libtoolkit/bitops.h>
#include <boost/function.hpp>
#include "common.h"
#include "rpc.h"
#include "rpc_service.h"
#include "config.h"
#include "flow.h"
#include "mysql_wrapper.h"

namespace cobaya {

using namespace RCF;
using namespace boost;
using namespace google::protobuf;

__thread MysqlWrapper *mysql;

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
	/* thread function */
	static void SlaveInit();
	static void SlaveExit();

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

static RpcServer g_server;

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

static int init_count;
static pthread_mutex_t init_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t init_cond = PTHREAD_COND_INITIALIZER;

static void wait_for_thread_registration(int nthreads)
{
	while (init_count < nthreads) {
		pthread_cond_wait(&init_cond, &init_lock);
	}
}

static void register_thread_initialized(void)
{
	pthread_mutex_lock(&init_lock);
	init_count++;
	pthread_cond_signal(&init_cond);
	pthread_mutex_unlock(&init_lock);
}

void RpcServer::SlaveInit()
{
	mysql = new MysqlWrapper();
	if (mysql == NULL) {
		DUMP_LOG("no memory");
		exit(EXIT_FAILURE);
	}
	if (mysql->Connect()) {
		DUMP_LOG("connect mysql error");
		exit(EXIT_FAILURE);
	}

	register_thread_initialized();
}

void init_mysql_for_sensor()
{
	mysql = new MysqlWrapper();
	if (mysql == NULL) {
		DUMP_LOG("no memory");
		exit(EXIT_FAILURE);
	}
	if (mysql->Connect()) {
		DUMP_LOG("connect mysql error");
		exit(EXIT_FAILURE);
	}
}

void RpcServer::SlaveExit()
{
	if (mysql == NULL)
		return;
	delete mysql;
	mysql = NULL;

	register_thread_initialized();
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
		ptr->addThreadInitFunctor(bind(&RpcServer::SlaveInit));
		ptr->addThreadDeinitFunctor(bind(&RpcServer::SlaveExit));

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

	/* Wait for all the threads to set themselves up before returning. */
	pthread_mutex_lock(&init_lock);
	wait_for_thread_registration(g_config.worker);
	pthread_mutex_unlock(&init_lock);

	return 0;
}

void stop_rpc_server()
{
	g_server.StopServer();

	/* Wait for all the threads to set themselves up before returning. */
	pthread_mutex_lock(&init_lock);
	init_count = 0;
	wait_for_thread_registration(g_config.worker);
	pthread_mutex_unlock(&init_lock);
}

} // namespace cobaya
