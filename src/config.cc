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

	config.daemon = iniparser_getboolean(ini, "cobaya:daemon", false);
	config.worker = iniparser_getint(ini, "cobaya:worker", 4);
	config.dir = iniparser_getstring(ini, "cobaya:dir", NULL);

	config.rpc_ip = iniparser_getstring(ini, "rpc:ip", NULL);
	config.rpc_port = iniparser_getint(ini, "rpc:port", 11611);

	config.mysql_cobaya_ip = iniparser_getstring(ini, "mysql:cobaya_ip", NULL);
	config.mysql_remote_ip = iniparser_getstring(ini, "mysql:remote_ip", NULL);
	config.mysql_user = iniparser_getstring(ini, "mysql:user", NULL);
	config.mysql_passwd = iniparser_getstring(ini, "mysql:passwd", NULL);
	config.mysql_db = iniparser_getstring(ini, "mysql:db", NULL);

	config.client_timeout = iniparser_getint(ini, "client:timeout", 60);
	config.client_heartbeat = iniparser_getint(ini, "client:heartbeat", 10);
	config.client_sensor = iniparser_getint(ini, "client:sensor", 10);
	config.client_fetch = iniparser_getint(ini, "client:fetch", 10);
	config.client_person = iniparser_getint(ini, "client:person", 5);

	config.compact_allow = iniparser_getboolean(ini, "compact:allow", true);
	config.compact_mysql = iniparser_getint(ini, "compact:mysql", 90);
	config.compact_flow = iniparser_getint(ini, "compact:flow", 2);

	config.watch_allow = iniparser_getboolean(ini, "watch:allow", false);
	config.watch_flow_life = iniparser_getint(ini, "watch:flow_life", 10);

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
