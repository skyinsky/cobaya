#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdint.h>

namespace cobaya {

struct Config {
	int worker;
	char *dir;

	char *rpc_ip;
	uint16_t rpc_port;
	uint16_t rpc_sport;

	char *mysql_cobaya_ip;
	char *mysql_remote_ip;
	char *mysql_user;
	char *mysql_passwd;
	char *mysql_db;

	int client_timeout;
	int client_check;
	int client_sensor;
	int client_fetch;

	bool compact_allow;
	int compact_mysql;
	int compact_flow;
};

extern Config g_config;

int load_config(const char *path);

} // namespace cobaya

#endif /* _CONFIG_H */
