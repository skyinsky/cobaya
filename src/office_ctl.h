#ifndef _OFFICE_CTL_H
#define _OFFICE_CTL_H

#include <stdint.h>
#include <libtoolkit/rbtree.h>

namespace cobaya {

/* 表'项目'  */
struct ItemDesc {
	uint32_t id;
	uint32_t code;
	char name[ITEM_NAME];

	rb_node node;			// 项目树节点
	ItemDesc *next;			// 项目链表节点
};

/* 表‘监控科室‘ */
struct OfficeCtl {
	OfficeCtl *next;

	uint32_t id;			// 监控科室编号
	rb_root tree;			// 项目树
	ItemDesc list_head;		// 项目链表
	void *head[ITEM_SIZE];		// FlowHead, 可执行项目类别，见表‘项目.项目编码‘

	char strid[OFFICE_ID];		// 监控科室编号
	char name[OFFICE_NAME];		// 监控科室名称
	char owner[OFFICE_OWNER];	// 所属院区
	char items[OFFICE_ITEM];	// 可执行项目集
};

extern OfficeCtl officectl_head;

int load_officectl_list();

} // namespace cobaya

#endif /* _OFFICE_CTL_H */
