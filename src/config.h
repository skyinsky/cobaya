#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdint.h>

namespace cobaya {

struct Config {
	bool daemon;
	int worker;

	char *rpc_ip;
	uint16_t rpc_port;

	char *mysql_ip;
	char *mysql_user;
	char *mysql_passwd;
	char *mysql_db;

	int client_timeout;
	int client_heartbeat;
	int client_sensor;

	bool compact_allow;
	int compact_interval;
};

extern Config g_config;
int load_config(const char *path);

} // namespace cobaya

#endif /* _CONFIG_H */
