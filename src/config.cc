#include <stdlib.h>
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
	config.worker = iniparser_getint(ini, "cobaya:worker", -1);

	config.rpc_ip = iniparser_getstring(ini, "rpc:ip", NULL);
	config.rpc_port = iniparser_getint(ini, "rpc:port", -1);

	config.mysql_ip = iniparser_getstring(ini, "mysql:ip", NULL);
	config.mysql_user = iniparser_getstring(ini, "mysql:user", NULL);
	config.mysql_passwd = iniparser_getstring(ini, "mysql:passwd", NULL);
	config.mysql_db = iniparser_getstring(ini, "mysql:db", NULL);

	config.client_timeout = iniparser_getint(ini, "client:timeout", -1);
	config.client_heartbeat = iniparser_getint(ini, "client:heartbeat", -1);
	config.client_sensor = iniparser_getint(ini, "client::sensor", -1);

	g_config = config;
	g_config.rpc_ip = strdup(config.rpc_ip);
	g_config.mysql_ip = strdup(config.mysql_ip);
	g_config.mysql_user = strdup(config.mysql_user);
	g_config.mysql_passwd = strdup(config.mysql_passwd);
	g_config.mysql_db = strdup(config.mysql_db);

	if (!g_config.rpc_ip || !g_config.mysql_ip ||
	    !g_config.mysql_user || !g_config.mysql_passwd ||
	    !g_config.mysql_db) {
		DUMP_LOG("no memory");
		ret = -1;
	}

	iniparser_freedict(ini);

	return ret;
}

} // namespace cobaya
