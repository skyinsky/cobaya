#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include "log.h"

namespace cobaya {

#define COBAYA_DEBUG	1

#define AUTH_KEY	"admin_*%$~!@#(*&^+_)_cobaya_58932145672103"

#define COBAYA_PREFIX	"cobaya: "

#define DUMP_LOG(fmt, ...) 					\
	log_msg("%s:%d, %s(): " fmt "\n",			\
		__FILE__,  __LINE__, __func__, ##__VA_ARGS__)

} // namespace cobaya

#endif /* _COMMON_H */
