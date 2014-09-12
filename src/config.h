#ifndef _CONFIG_H
#define _CONFIG_H

#include "libiniparser/iniparser.h"

namespace cobaya {

struct Config {
	int daemon;
	int worker;

	char *rpc_ip;
	int rpc_port;

	char *mysql_ip;
	char *mysql_user;
	char *mysql_passwd;

	int client_timeout;

	dictionary *_ini;
};

} // namespace cobaya

#endif /* _CONFIG_H */
