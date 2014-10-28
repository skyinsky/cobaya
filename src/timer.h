#ifndef _TIMER_H
#define _TIMER_H

#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <event.h>
#include <libtoolkit/common.h>
#include "common.h"

namespace cobaya {

typedef void (*timer_callback)(void *arg);

/* millisecond timer event */
class Timer {
public:
	Timer() { memset(this, 0, sizeof(*this)); }

	/* ugly */
	void Set(event_base *base, uint64_t msec,
		 timer_callback cb, void *arg);

	static int  SchedOneshot(Timer *t);
	static int  SchedPersist(Timer *t);
	static void SchedCancel(Timer *t);

private:
	static void default_callback(int, short, void *);
	static void oneshot_callback(int , short, void *);
	static void persist_callback(int, short, void *);

private:
	struct event ev;
	timeval tv;

	timer_callback cb;
	void *arg;
};

inline void Timer::Set(event_base *base, uint64_t ms,
		       timer_callback cb, void *arg)
{
	assert(ms > 0);
	assert(cb != NULL);
	assert(base != NULL);

	this->cb = cb;
	this->arg = arg;

	if (ms > 1000) {
		tv.tv_sec = ms / 1000;
		tv.tv_usec = (ms % 1000) * 1000;
	} else {
		tv.tv_sec = 0;
		tv.tv_usec = ms * 1000;
	}

	evtimer_assign(&ev, base, default_callback, NULL);
}

inline int Timer::SchedOneshot(Timer *t)
{
	int err = 0;
	event_base *base;

	if (unlikely(event_get_callback(&t->ev)
	    != default_callback)) {
		DUMP_LOG("timer not initialized");
		err = -1;
		goto out;
	}

	base = event_get_base(&t->ev);
	if (unlikely(evtimer_assign(&t->ev, base,
				    oneshot_callback, t))) {
		DUMP_LOG("assign timer error");
		err = -1;
		goto out;
	}

	if (unlikely(evtimer_add(&t->ev, &t->tv))) {
		evtimer_assign(&t->ev, base,
			       default_callback, NULL);
		DUMP_LOG("add timer error");
		err = -1;
		goto out;
	}

out:
	return err;
}

inline int Timer::SchedPersist(Timer *t)
{
	int err = 0;
	event_base *base;

	if (unlikely(event_get_callback(&t->ev)
	    != default_callback)) {
		DUMP_LOG("timer not initialized");
		err = -1;
		goto out;
	}

	base = event_get_base(&t->ev);
	if (unlikely(event_assign(&t->ev, base, -1, EV_PERSIST,
				  persist_callback, t))) {
		DUMP_LOG("assign timer error");
		err = -1;
		goto out;
	}

	if (unlikely(evtimer_add(&t->ev, &t->tv))) {
		evtimer_assign(&t->ev, base,
			       default_callback, NULL);
		DUMP_LOG("add timer error");
		err = -1;
		goto out;
	}

out:
	return err;
}

inline void Timer::SchedCancel(Timer *t)
{
	event_base *base;

	if (event_get_callback(&t->ev)
	    == default_callback) {
		return;
	}

	base = event_get_base(&t->ev);
	evtimer_del(&t->ev);
	evtimer_assign(&t->ev, base, default_callback, NULL);
}

} // namespace cobaya

#endif /* _TIMER_H */
