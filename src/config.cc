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

	config.daemon = iniparser_getboolean(ini, "cobaya:daemon", true);
	config.worker = iniparser_getint(ini, "cobaya:worker", -1);
	config.dir = iniparser_getstring(ini, "cobaya:dir", NULL);

	config.rpc_ip = iniparser_getstring(ini, "rpc:ip", NULL);
	config.rpc_port = iniparser_getint(ini, "rpc:port", -1);

	config.mysql_cobaya_ip = iniparser_getstring(ini, "mysql:cobaya_ip", NULL);
	config.mysql_remote_ip = iniparser_getstring(ini, "mysql:remote_ip", NULL);
	config.mysql_user = iniparser_getstring(ini, "mysql:user", NULL);
	config.mysql_passwd = iniparser_getstring(ini, "mysql:passwd", NULL);
	config.mysql_db = iniparser_getstring(ini, "mysql:db", NULL);

	config.client_timeout = iniparser_getint(ini, "client:timeout", -1);
	config.client_heartbeat = iniparser_getint(ini, "client:heartbeat", -1);
	config.client_sensor = iniparser_getint(ini, "client:sensor", -1);

	config.compact_allow = iniparser_getboolean(ini, "compact:allow", true);
	config.compact_interval = iniparser_getint(ini, "compact:interval", 30);

	g_config = config;
	g_config.dir = strdup(config.dir);
	g_config.rpc_ip = strdup(config.rpc_ip);
	g_config.mysql_cobaya_ip = strdup(config.mysql_cobaya_ip);
	g_config.mysql_remote_ip = strdup(config.mysql_remote_ip);
	g_config.mysql_user = strdup(config.mysql_user);
	g_config.mysql_passwd = strdup(config.mysql_passwd);
	g_config.mysql_db = strdup(config.mysql_db);

	if (!g_config.rpc_ip || !g_config.mysql_cobaya_ip ||
	    !g_config.mysql_remote_ip || !g_config.mysql_user ||
	    !g_config.mysql_passwd || !g_config.mysql_db ||
	    !g_config.dir) {
		DUMP_LOG("no memory");
		ret = -1;
	}

	iniparser_freedict(ini);

	return ret;
}

} // namespace cobaya
