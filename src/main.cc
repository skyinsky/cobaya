#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "mysql_wrapper.h"
#include "common.h"
#include "config.h"
#include "rpc.h"

using namespace cobaya;

namespace {

static Config config;
static RpcServer server;

#define DUMP_CALL(x)		\
do {				\
	int res = (x);		\
	if (res != 0) {		\
		DUMP_LOG();	\
		return res;	\
	}			\
} while(0)

int prepare_config(const char *path)
{
	dictionary *ini;

	config._ini = iniparser_load(path);
	if (config._ini == NULL) {
		DUMP_LOG();
		return -1;
	}
	ini = config._ini;

	config.daemon = iniparser_getboolean(ini, "cobaya:daemon", -1);
	config.worker = iniparser_getint(ini, "cobaya:worker", -1);

	config.rpc_ip = iniparser_getstring(ini, "rpc:ip", NULL);
	config.rpc_port = iniparser_getint(ini, "rpc:port", -1);

	config.mysql_ip = iniparser_getstring(ini, "mysql:ip", NULL);
	config.mysql_user = iniparser_getstring(ini, "mysql:user", NULL);
	config.mysql_passwd = iniparser_getstring(ini, "mysql:passwd", NULL);

	config.client_timeout = iniparser_getint(ini, "client:timeout", -1);

	return 0;
}

int prepare_server(Config *conf)
{
	DUMP_CALL(server.Init());
	DUMP_CALL(server.AddEndpoint(conf->rpc_ip, conf->rpc_port));
	DUMP_CALL(server.CreateThreadPool(conf->worker));
	DUMP_CALL(server.StartServer());

	return 0;
}

inline void release_config()
{
	iniparser_freedict(config._ini);
	memset(&config, 0, sizeof(config));
}

inline void release_server()
{
	server.StopServer();
}

} // anonymous namespace

int main(int argc, char *argv[])
{
	int res;

	DUMP_CALL(prepare_config("cobaya.ini"));
	DUMP_CALL(prepare_server(&config));

not_used:
	release_config();

	/* wait */
	getchar();

exit_free:	
	release_server();

	return 0;
}
