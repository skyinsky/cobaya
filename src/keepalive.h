#ifndef _KEEPALIVE_H
#define _KEEPALIVE_H

#include <time.h>
#include <event2/event.h>
#include "libtoolkit/include/list.h"
#include "libtoolkit/include/rwlock.h"
#include "libtoolkit/include/kref.h"

namespace cobaya {

#define OBJ_GET_PUT(type, release)	\
	type* Get() {			\
		kref(&this->ref); 	\
		return this;		\
	}				\
	void Put() {			\
		kref_put(&this->ref,	\
			 release);	\
	}				\
	kref ref

#define DEV_CODE	10
#define DEV_NAME	20
#define DEV_ENDPOINT	20
#define DEV_OWNER	10

struct DevDesc {
	list_head list;
	
	/* timer event */
	event ev;

	time_t update_time;	/* clock_gettime */

	/* mysql:table, 设备表 */
	char code[DEV_CODE];
	char name[DEV_NAME];
	char endpoint[DEV_ENDPOINT];
	char owner[DEV_OWNER];

	OBJ_GET_PUT(DevDesc, free);
};

class KeepAlive {
public:
	KeepAlive(event_base *ev_base);
	~KeepAlive();

	/* init medical dev from mysql */
	int LoadDevices(Config *conf);

private:
	/* medical dev list */
	list_head list;
	rwlock_t lock;
};

} // namespace cobaya

#endif /* _KEEPALIVE_H */
