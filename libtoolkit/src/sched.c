#include <limits.h>
#include <pthread.h>
#include <libtoolkit/common.h>
#include <libtoolkit/bitops.h>
#include <libtoolkit/wait.h>
#include <libtoolkit/completion.h>

void add_wait_queue(wait_queue_head_t *q, wait_queue_t *wait)
{
	wait->flags &= ~WQ_FLAG_EXCLUSIVE;
	pthread_mutex_lock(&q->lock);
	__add_wait_queue(q, wait);
	pthread_mutex_unlock(&q->lock);
}

void add_wait_queue_exclusive(wait_queue_head_t *q, wait_queue_t *wait)
{
	wait->flags |= WQ_FLAG_EXCLUSIVE;
	pthread_mutex_lock(&q->lock);
	__add_wait_queue_tail(q, wait);
	pthread_mutex_unlock(&q->lock);
}

void remove_wait_queue(wait_queue_head_t *q, wait_queue_t *wait)
{
	pthread_mutex_lock(&q->lock);
	__remove_wait_queue(q, wait);
	pthread_mutex_unlock(&q->lock);
}

void prepare_to_wait(wait_queue_head_t *q, wait_queue_t *wait)
{
	wait->flags &= ~WQ_FLAG_EXCLUSIVE;
	pthread_mutex_lock(&q->lock);
	if (list_empty(&wait->task_list))
		__add_wait_queue(q, wait);
	__clear_bit(WQ_FLAG_RUNNING, &wait->flags);
	pthread_mutex_unlock(&q->lock);
}

void prepare_to_wait_exclusive(wait_queue_head_t *q, wait_queue_t *wait)
{
	wait->flags |= WQ_FLAG_EXCLUSIVE;
	pthread_mutex_lock(&q->lock);
	if (list_empty(&wait->task_list))
		__add_wait_queue_tail(q, wait);
	__clear_bit(WQ_FLAG_RUNNING, &wait->flags);
	pthread_mutex_unlock(&q->lock);
}

/*
 * finish_wait - clean up after waiting in a queue
 * @q: waitqueue waited on
 * @wait: wait descriptor
 *
 * Sets current thread back to running state and removes
 * the wait descriptor from the given waitqueue if still
 * queued.
 */
void finish_wait(wait_queue_head_t *q, wait_queue_t *wait)
{
	__set_bit(WQ_FLAG_RUNNING, &wait->flags);
	/*
	 * We can check for list emptiness outside the lock
	 * IFF:
	 *  - we use the "careful" check that verifies both
	 *    the next and prev pointers, so that there cannot
	 *    be any half-pending updates in progress on other
	 *    CPU's that we haven't seen yet (and that might
	 *    still change the stack area.
	 * and
	 *  - all other users take the lock (ie we can only
	 *    have _one_ other CPU that looks at or modifies
	 *    the list).
	 */
	if (!list_empty_careful(&wait->task_list)) {
		pthread_mutex_lock(&q->lock);
		list_del_init(&wait->task_list);
		pthread_mutex_unlock(&q->lock);
	}
}

void default_wake_function(wait_queue_t *curr)
{
	pthread_mutex_lock(&curr->lock);
	__set_bit(WQ_FLAG_RUNNING, &curr->flags);
	pthread_cond_signal(&curr->cond);
	pthread_mutex_unlock(&curr->lock);
}

void autoremove_wake_function(wait_queue_t *wait)
{
	default_wake_function(wait);
	list_del_init(&wait->task_list);
}

/*
 * The core wakeup function. Non-exclusive wakeups (nr_exclusive == 0) just
 * wake everything up. If it's an exclusive wakeup (nr_exclusive == small +ve
 * number) then we wake all the non-exclusive tasks and one exclusive task.
 *
 * There are circumstances in which we can try to wake a task which has already
 * started to run but is not in state TASK_RUNNING. try_to_wake_up() returns
 * zero in this (rare) case, and we handle it by continuing to scan the queue.
 */
static inline void __wake_up_common(wait_queue_head_t *q, int nr_exclusive)
{
	wait_queue_t *curr, *next;

	list_for_each_entry_safe(curr, next, &q->task_list, task_list) {
		unsigned flags = curr->flags;

		curr->func(curr);
		if ((flags & WQ_FLAG_EXCLUSIVE) && !--nr_exclusive)
			break;
	}
}

/**
 * __wake_up - wake up threads blocked on a waitqueue.
 * @q: the waitqueue
 * @nr_exclusive: how many wake-one or wake-many threads to wake up
 *
 * It may be assumed that this function implies a write memory barrier before
 * changing the task state if and only if any tasks are woken up.
 */
void __wake_up(wait_queue_head_t *q, int nr_exclusive)
{
	pthread_mutex_lock(&q->lock);
	__wake_up_common(q, nr_exclusive);
	pthread_mutex_unlock(&q->lock);
}

/*
 * Same as __wake_up but called with the lock in wait_queue_head_t held.
 */
void __wake_up_locked(wait_queue_head_t *q)
{
	__wake_up_common(q, 1);
}

/**
 * wait_for_completion: - waits for completion of a task
 * @x:  holds the state of this particular completion
 *
 * This waits to be signaled for completion of a specific task. It is NOT
 * interruptible and there is no timeout.
 *
 * See also similar routines (i.e. wait_for_completion_timeout()) with timeout
 * and interrupt capability. Also see complete().
 */
void wait_for_completion(struct completion *x)
{
	wait_event(x->wait, x->done);
}

/**
 * wait_for_completion_timeout: - waits for completion of a task (w/timeout)
 * @x:  holds the state of this particular completion
 * @timeout:  timeout value in millisecond
 *
 * This waits for either a completion of a specific task to be signaled or for a
 * specified timeout to expire. The timeout is in jiffies. It is not
 * interruptible.
 */
int wait_for_completion_timeout(struct completion *x,
				unsigned long timeout)
{
	return wait_event_timeout(x->wait, x->done, timeout);
}

/**
 * complete: - signals a single thread waiting on this completion
 * @x:  holds the state of this particular completion
 *
 * This will wake up a single thread waiting on this completion. Threads will be
 * awakened in the same order in which they were queued.
 *
 * See also complete_all(), wait_for_completion() and related routines.
 *
 * It may be assumed that this function implies a write memory barrier before
 * changing the task state if and only if any tasks are woken up.
 */
void complete(struct completion *x)
{
	pthread_mutex_lock(&x->wait.lock);
	x->done++;
	__wake_up_common(&x->wait, 1);
	pthread_mutex_unlock(&x->wait.lock);
}

/**
 * complete_all: - signals all threads waiting on this completion
 * @x:  holds the state of this particular completion
 *
 * This will wake up all threads waiting on this particular completion event.
 *
 * It may be assumed that this function implies a write memory barrier before
 * changing the task state if and only if any tasks are woken up.
 */
void complete_all(struct completion *x)
{
	pthread_mutex_lock(&x->wait.lock);
	x->done += UINT_MAX/2;
	__wake_up_common(&x->wait, 0);
	pthread_mutex_unlock(&x->wait.lock);
}

/**
 * completion_done - Test to see if a completion has any waiters
 * @x:	completion structure
 *
 * Returns: 0 if there are waiters (wait_for_completion() in progress)
 *	    1 if there are no waiters.
 *
 */
bool completion_done(struct completion *x)
{
	int ret = 1;

	pthread_mutex_lock(&x->wait.lock);
	if (!x->done)
		ret = 0;
	pthread_mutex_unlock(&x->wait.lock);
	return ret;
}
