#ifndef _COMMON_H
#define _COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

namespace cobaya {

#define AUTH_KEY	"admin_*%$~!@#(*&^+_)_cobaya_58932145672103"

#define COBAYA_PREFIX	"cobaya: "

#define DUMP_LOG(fmt, ...) 					\
	log_msg("%s:%d, %s(): " fmt "\n",			\
		__FILE__,  __LINE__, __func__, ##__VA_ARGS__)

#define COBAYA_DEBUG	1

#define USER_ID		11	/* 病人唯一号 */
#define USER_NAME	20	/* 姓名 */
#define APPLY_ID	20	/* 申请单号 */

#define OFFICE_ID	20	/* 科室编号 */
#define OFFICE_NAME	30	/* 科室名称 */
#define OFFICE_OWNER	30	/* 院区 */
#define OFFICE_ITEM	20	/* 执行项目 */

#define DEV_CODE	10	/* 器械编码 */
#define DEV_NAME	20	/* 器械名称 */
#define DEV_HOST	20	/* 管理终端 */

#define ITEM_ID		20	/* 项目编号 */
#define ITEM_NAME	60	/* 项目名称 */
#define ITEM_CODE	4	/* 项目编码 */
#define ITEM_SIZE	4	/* 项目类别 */
#define ITEM_CHILD	50	/* 子项目数 */
#define ITEM_FS		0
#define ITEM_HC		1
#define ITEM_CT		2
#define ITEM_CS		3

#define ITEM_HEAD(type)				\
({						\
	int t = -1;				\
	if (!strncmp((type), "FS", 2)) {	\
		t = ITEM_FS;			\
		goto _get;			\
	}					\
	if (!strncmp((type), "HC", 2)) {	\
		t = ITEM_HC;			\
		goto _get;			\
	}					\
	if (!strncmp((type), "CT", 2)) {	\
		t = ITEM_CT;			\
		goto _get;			\
	}					\
	if (!strncmp((type), "CS", 2)) {	\
		t = ITEM_CS;			\
		goto _get;			\
	}					\
	DUMP_LOG("error type (%s)", (type));	\
	exit(EXIT_FAILURE);			\
_get:	t;					\
})

#define HEAD_ITEM(code)				\
({						\
 	char *p = NULL;				\
 	switch (code) {				\
 	case ITEM_FS:				\
 		p = (char *)"FS";		\
		break;				\
	case ITEM_HC:				\
 		p = (char *)"HC";		\
		break;				\
 	case ITEM_CT:				\
 		p = (char *)"CT";		\
 		break;				\
 	case ITEM_CS:				\
 		p = (char *)"CS";		\
 		break;				\
 	default:				\
		DUMP_LOG("error (%s)", (code));	\
		exit(EXIT_FAILURE);		\
 	}					\
	p;					\
})

} // namespace cobaya

#endif /* _COMMON_H */
