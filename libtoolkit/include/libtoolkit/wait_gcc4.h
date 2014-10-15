#ifndef _LIBTOOLKIT_WAIT_CPP_H
#define _LIBTOOLKIT_WAIT_CPP_H

#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <libtoolkit/list.h>
#include <libtoolkit/bitops.h>

#ifdef __cplusplus
extern "C" {
#endif

#define new not_keyword

typedef struct __wait_queue wait_queue_t;
typedef void (*wait_queue_func_t)(wait_queue_t *wait);
void default_wake_function(wait_queue_t *wait);

struct __wait_queue {
#define WQ_FLAG_EXCLUSIVE	0x01
#define WQ_FLAG_RUNNING		0x02
	unsigned long flags;
	wait_queue_func_t func;
	struct list_head task_list;

	pthread_mutex_t lock;
	pthread_cond_t cond;
};

struct __wait_queue_head {
	pthread_mutex_t lock;
	struct list_head task_list;
};
typedef struct __wait_queue_head wait_queue_head_t;

/*
 * Macros for declaration and initialisaton of the datatypes
 */

#define __WAITQUEUE_INITIALIZER(name) {					\
	flags		: 0,						\
	func		: default_wake_function,			\
	task_list	: { NULL, NULL },				\
	lock		: PTHREAD_MUTEX_INITIALIZER,			\
	cond		: PTHREAD_COND_INITIALIZER			\
}

#define DECLARE_WAITQUEUE(name)						\
	wait_queue_t name = __WAITQUEUE_INITIALIZER(name)

#define __WAIT_QUEUE_HEAD_INITIALIZER(name) {				\
	lock		: PTHREAD_MUTEX_INITIALIZER,			\
	task_list	: { &(name).task_list, &(name).task_list }	\
}

#define DECLARE_WAIT_QUEUE_HEAD(name) \
	wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)

static inline void init_waitqueue_head(wait_queue_head_t *q)
{
	pthread_mutex_init(&q->lock, NULL);
	INIT_LIST_HEAD(&q->task_list);
}

static inline void init_waitqueue_entry(wait_queue_t *q)
{
	q->flags = 0;
	q->func = default_wake_function;
	pthread_mutex_init(&q->lock, NULL);
	pthread_cond_init(&q->cond, NULL);
}

static inline void init_waitqueue_func_entry(wait_queue_t *q,
					     wait_queue_func_t func)
{
	q->flags = 0;
	q->func = func;
	pthread_mutex_init(&q->lock, NULL);
	pthread_cond_init(&q->cond, NULL);
}

static inline int waitqueue_active(wait_queue_head_t *q)
{
	return !list_empty(&q->task_list);
}

extern void add_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);
extern void add_wait_queue_exclusive(wait_queue_head_t *q, wait_queue_t *wait);
extern void remove_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);

static inline void __add_wait_queue(wait_queue_head_t *head, wait_queue_t *new)
{
	list_add(&new->task_list, &head->task_list);
}

/*
 * Used for wake-one threads:
 */
static inline void __add_wait_queue_exclusive(wait_queue_head_t *q,
					      wait_queue_t *wait)
{
	wait->flags |= WQ_FLAG_EXCLUSIVE;
	__add_wait_queue(q, wait);
}

static inline void __add_wait_queue_tail(wait_queue_head_t *head,
					 wait_queue_t *new)
{
	list_add_tail(&new->task_list, &head->task_list);
}

static inline void __add_wait_queue_tail_exclusive(wait_queue_head_t *q,
						   wait_queue_t *wait)
{
	wait->flags |= WQ_FLAG_EXCLUSIVE;
	__add_wait_queue_tail(q, wait);
}

static inline void __remove_wait_queue(wait_queue_head_t *head,
				       wait_queue_t *old)
{
	list_del(&old->task_list);
}

void __wake_up(wait_queue_head_t *q, int nr);
void __wake_up_locked(wait_queue_head_t *q);

#define wake_up(x)		__wake_up(x, 1)
#define wake_up_nr(x, nr)	__wake_up(x, nr)
#define wake_up_all(x)		__wake_up(x, 0)
#define wake_up_locked(x)	__wake_up_locked(x, 1)

#define __wait_event(wq, condition) 					\
do {									\
	DEFINE_WAIT(__wait);						\
									\
	for (;;) {							\
		prepare_to_wait(&wq, &__wait);				\
		if (condition)						\
			break;						\
		schedule(&__wait);					\
	}								\
	finish_wait(&wq, &__wait);					\
} while (0)

/**
 * wait_event - sleep until a condition gets true
 * @wq: the waitqueue to wait on
 * @condition: a C expression for the event to wait for
 *
 * The process is put to sleep until the @condition evaluates
 * to true. The @condition is checked each time the waitqueue
 * @wq is woken up.
 *
 * wake_up() has to be called after changing any variable that
 * could change the result of the wait condition.
 */
#define wait_event(wq, condition) 					\
do {									\
	if (condition)	 						\
		break;							\
	__wait_event(wq, condition);					\
} while (0)

#define __wait_event_timeout(wq, condition, ret)			\
do {									\
	DEFINE_WAIT(__wait);						\
									\
	for (;;) {							\
		prepare_to_wait(&wq, &__wait);				\
		if (condition)						\
			break;						\
		ret = schedule_timeout(&__wait, ret);			\
		if (!ret || ret == ETIMEDOUT)				\
			break;						\
	}								\
	finish_wait(&wq, &__wait);					\
} while (0)

/**
 * wait_event_timeout - sleep until a condition gets true or a timeout elapses
 * @wq: the waitqueue to wait on
 * @condition: a C expression for the event to wait for
 * @timeout: timeout, in millisecond
 *
 * The process is put to sleep until the
 * @condition evaluates to true. The @condition is checked each time
 * the waitqueue @wq is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the wait condition.
 *
 * The function returns ETIMEDOUT if the @timeout elapsed, or zeor if the
 * @condition evaluates to true.
 */
#define wait_event_timeout(wq, condition, timeout)			\
({									\
	long __ret = timeout;						\
	if (!(condition)) 						\
		__wait_event_timeout(wq, condition, __ret);		\
	__ret;								\
})

/*
 * Waitqueues which are removed from the waitqueue_head at wakeup time
 */
void prepare_to_wait(wait_queue_head_t *q, wait_queue_t *wait);
void prepare_to_wait_exclusive(wait_queue_head_t *q, wait_queue_t *wait);
void finish_wait(wait_queue_head_t *q, wait_queue_t *wait);
void autoremove_wake_function(wait_queue_t *wait);

#define DEFINE_WAIT_FUNC(name, function)				\
	wait_queue_t name = {						\
		flags		: 0,					\
		func		: function,				\
		task_list	: LIST_HEAD_INIT((name).task_list),	\
		lock		: PTHREAD_MUTEX_INITIALIZER,		\
		cond		: PTHREAD_COND_INITIALIZER		\
	}

#define DEFINE_WAIT(name) DEFINE_WAIT_FUNC(name, autoremove_wake_function)

#define init_wait(wait)							\
	do {								\
		(wait)->func = autoremove_wake_function;		\
		INIT_LIST_HEAD(&(wait)->task_list);			\
		pthread_mutex_init(&wait->lock, NULL);			\
		pthread_cond_init(&wait->cond, NULL);			\
	} while (0)

#define schedule(wait)							\
do {									\
	pthread_mutex_lock(&(wait)->lock);				\
	if (test_bit(WQ_FLAG_RUNNING, &(wait)->flags))	{		\
		pthread_mutex_unlock(&(wait)->lock);			\
		break;							\
	}								\
	pthread_cond_wait(&(wait)->cond, &(wait)->lock);		\
	pthread_mutex_unlock(&(wait)->lock);				\
} while (0)

#define schedule_timeout(wait, msec)					\
({									\
 	int ret = 0, sec = msec / 1000;					\
	struct timespec ts;						\
 									\
 	pthread_mutex_lock(&(wait)->lock);				\
	if (test_bit(WQ_FLAG_RUNNING, &(wait)->flags))	{		\
		pthread_mutex_unlock(&(wait)->lock);			\
 		goto wake_up_now;					\
	}								\
	clock_gettime(CLOCK_REALTIME, &ts);				\
 	ts.tv_sec += sec;						\
 	ts.tv_nsec += (msec % 1000) * 1000 * 1000;			\
 	ret = pthread_cond_timedwait(&(wait)->cond, &(wait)->lock, &ts);\
 	pthread_mutex_unlock(&(wait)->lock);				\
 	wake_up_now: ret;						\
})

#undef new

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_WAIT_CPP_H */
