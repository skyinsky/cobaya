#ifndef _OFFICE_H
#define _OFFICE_H

namespace cobaya {

#define OFFICE_LEN	20

struct OfficeDesc {
	OfficeDesc *next;

	/* mysql:table, 科室表 */
	uint32_t id;
	char name[OFFICE_LEN];
};

extern OfficeDesc *offices;

int load_office_list();

} // namespace cobaya

#endif /* _OFFICE_H */
