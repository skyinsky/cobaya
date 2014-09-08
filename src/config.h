#ifndef _CONFIG_H
#define _CONFIG_H

#include "libiniparser/iniparser.h"

namespace cobaya {

struct Config {
	int daemon;

	char *rpc_ip;
	int rpc_port;
	int rpc_worker;

	char *mysql_ip;
	char *mysql_user;
	char *mysql_passwd;

	dictionary *_ini;
};

} // namespace cobaya

#endif /* _CONFIG_H */
