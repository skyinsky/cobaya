#include <stdlib.h>
#include "timer.h"

namespace cobaya {

void Timer::default_callback(int fd, short ev, void *arg)
{
	DUMP_LOG("something very bad happened");
	exit(EXIT_FAILURE);
}

void Timer::oneshot_callback(int fd, short ev, void *arg)
{
	event_base *base;
	Timer *t = (Timer *)arg;

	t->cb(t->arg);

	base = event_get_base(&t->ev);
	evtimer_assign(&t->ev, base, default_callback, NULL);
}

void Timer::persist_callback(int fd, short ev, void *arg)
{
	Timer *t = (Timer *)arg;

	t->cb(t->arg);
}

} // namespace cobaya
