#ifndef _HIS_H
#define _HIS_H

#include <stdint.h>
#include "common.h"

namespace cobaya {

struct HisDesc {
	uint64_t user_id;
	uint32_t item_id;
	uint32_t exe_office_id;
	uint32_t app_office_id;
	char apply_id[APPLY_ID];
	char user[USER_NAME];
	char doctor[USER_NAME];
};

} // namespace cobaya

#endif /* _HIS_H */
