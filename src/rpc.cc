#include <string.h>
#include <iostream>
#include "rpc.h"
#include "common.h"

namespace cobaya {

using namespace RCF;
using namespace google::protobuf;

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
		std::cout << COBAYA_PREFIX << e.getErrorString() << std::endl;
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
		std::cout << COBAYA_PREFIX << e.getErrorString() << std::endl;
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
		std::cout << COBAYA_PREFIX << e.getErrorString() << std::endl;
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
		std::cout << COBAYA_PREFIX << e.getErrorString() << std::endl;
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
		std::cout << COBAYA_PREFIX << e.getErrorString() << std::endl;
	}

	_exit();
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
		std::cout << COBAYA_PREFIX << e.getErrorString() << std::endl;
		res = -1;
	}

	return res;

}















}
