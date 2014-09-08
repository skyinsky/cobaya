#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>

namespace cobaya {

#define COBAYA_PREFIX	"cobaya: "

#define DUMP_LOG(fmt, ...) \
	printf(COBAYA_PREFIX "%s:%d: " fmt "\n",  __func__, __LINE__, ##__VA_ARGS__)

} // namespace cobaya

#endif /* _COMMON_H */
