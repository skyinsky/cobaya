#ifndef _OFFICE_H
#define _OFFICE_H

#include "common.h"

namespace cobaya {

struct OfficeDesc {
	OfficeDesc *next;

	/* mysql:table, 科室表 */
	uint32_t id;
	char name[OFFICE_NAME];
};

extern OfficeDesc *offices;

int load_office_list();

} // namespace cobaya

#endif /* _OFFICE_H */
