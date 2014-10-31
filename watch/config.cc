#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libiniparser/iniparser.h>
#include "common.h"
#include "config.h"

namespace cobaya {

Config g_config;

int load_config(const char *path)
{
	int ret = 0;
	dictionary *ini;
	Config config;

	ini = iniparser_load(path);
	if (ini == NULL) {
		DUMP_LOG("load %s error", path);
		return -1;
	}

	config.daemon = iniparser_getboolean(ini, "cobaya:daemon", -1);
	config.start_sys = iniparser_getint(ini, "monitor:start_sys", -1);

	config.rpc_ip = iniparser_getstring(ini, "rpc:ip", NULL);
	config.rpc_port = iniparser_getint(ini, "rpc:port", -1);

	g_config = config;
	g_config.rpc_ip = strdup(config.rpc_ip);

	if (g_config.rpc_ip == NULL) {
		DUMP_LOG("no memory");
		ret = -1;
	}

	iniparser_freedict(ini);

	return ret;
}

} // namespace cobaya
