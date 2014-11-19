#ifndef _OFFICE_CTL_H
#define _OFFICE_CTL_H

#include <stdint.h>
#include <libtoolkit/rbtree.h>

namespace cobaya {

struct ItemDesc {
	uint32_t id;
	uint32_t code;
	char name[ITEM_NAME];

	rb_node node;
};

struct OfficeCtl {
	OfficeCtl *next;

	uint32_t id;
	rb_root tree;
	void *head[ITEM_SIZE];

	char strid[OFFICE_ID];
	char name[OFFICE_NAME];
	char owner[OFFICE_OWNER];
	char items[OFFICE_ITEM];
};

extern OfficeCtl officectl_head;

int load_officectl_list();

} // namespace cobaya

#endif /* _OFFICE_CTL_H */
