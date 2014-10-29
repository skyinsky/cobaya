#ifndef _OFFICE_H
#define _OFFICE_H

namespace cobaya {

#define OFFICE_LEN	10

struct OfficeDesc {
	OfficeDesc *next;

	/* mysql:table, 科室表 */
	char name[OFFICE_LEN];
};

extern OfficeDesc office_head;

int load_office_list();

} // namespace cobaya

#endif /* _OFFICE_H */