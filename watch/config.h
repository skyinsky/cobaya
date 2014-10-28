#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdint.h>

namespace cobaya {

struct Config {
	char *rpc_ip;
	uint16_t rpc_port;

	bool daemon;
	int start_sys;
};

extern Config g_config;
int load_config(const char *path);

} // namespace cobaya

#endif /* _CONFIG_H */
