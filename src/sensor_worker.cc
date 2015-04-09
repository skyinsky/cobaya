#include <sys/types.h>
#include <sys/prctl.h>

#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include <libtoolkit/completion.h>
#include <libtoolkit/random.h>
#include <libtoolkit/bug.h>
#include <libtoolkit/socket.h>

#include "common.h"
#include "dev.h"
#include "rpc.h"
#include "config.h"
#include "flow.h"
#include "main.h"
#include "connect.h"
#include "sensor_server.h"
#include "sensor_worker.h"

namespace cobaya {

//-----------------------------------------------------
// connection queue
//-----------------------------------------------------
#define ITEMS_PER_ALLOC 1024

/* An item in the connection queue. */
typedef struct conn_queue_item CQ_ITEM;
struct conn_queue_item {
    int               sfd;
    CQ_ITEM          *next;
};

/* A connection queue. */
typedef struct conn_queue CQ;
struct conn_queue {
    CQ_ITEM *head;
    CQ_ITEM *tail;
    pthread_mutex_t lock;
    pthread_cond_t  cond;
};

/* Free list of CQ_ITEM structs */
static CQ_ITEM *cqi_freelist;
static pthread_mutex_t cqi_freelist_lock;

/*
 * Initializes a connection queue.
 */
static void cq_init(CQ *cq) {
    pthread_mutex_init(&cq->lock, NULL);
    pthread_cond_init(&cq->cond, NULL);
    cq->head = NULL;
    cq->tail = NULL;
}

/*
 * Looks for an item on a connection queue, but doesn't block if there isn't
 * one.
 * Returns the item, or NULL if no item is available
 */
static CQ_ITEM *cq_pop(CQ *cq) {
    CQ_ITEM *item;

    pthread_mutex_lock(&cq->lock);
    item = cq->head;
    if (NULL != item) {
        cq->head = item->next;
        if (NULL == cq->head)
            cq->tail = NULL;
    }
    pthread_mutex_unlock(&cq->lock);

    return item;
}

/*
 * Adds an item to a connection queue.
 */
static void cq_push(CQ *cq, CQ_ITEM *item) {
    item->next = NULL;

    pthread_mutex_lock(&cq->lock);
    if (NULL == cq->tail)
        cq->head = item;
    else
        cq->tail->next = item;
    cq->tail = item;
    pthread_cond_signal(&cq->cond);
    pthread_mutex_unlock(&cq->lock);
}

/*
 * Returns a fresh connection queue item.
 */
static CQ_ITEM *cqi_new(void) {
    CQ_ITEM *item = NULL;
    pthread_mutex_lock(&cqi_freelist_lock);
    if (cqi_freelist) {
        item = cqi_freelist;
        cqi_freelist = item->next;
    }
    pthread_mutex_unlock(&cqi_freelist_lock);

    if (NULL == item) {
        int i;

        /* Allocate a bunch of items at once to reduce fragmentation */
        item = (CQ_ITEM *)malloc(sizeof(CQ_ITEM) * ITEMS_PER_ALLOC);
        if (NULL == item)
            return NULL;

        /*
         * Link together all the new items except the first one
         * (which we'll return to the caller) for placement on
         * the freelist.
         */
        for (i = 2; i < ITEMS_PER_ALLOC; i++)
            item[i - 1].next = &item[i];

        pthread_mutex_lock(&cqi_freelist_lock);
        item[ITEMS_PER_ALLOC - 1].next = cqi_freelist;
        cqi_freelist = &item[1];
        pthread_mutex_unlock(&cqi_freelist_lock);
    }

    return item;
}


/*
 * Frees a connection queue item (adds it to the freelist.)
 */
static void cqi_free(CQ_ITEM *item) {
    pthread_mutex_lock(&cqi_freelist_lock);
    item->next = cqi_freelist;
    cqi_freelist = item;
    pthread_mutex_unlock(&cqi_freelist_lock);
}

//-----------------------------------------------------
// sensor slaves
//-----------------------------------------------------
typedef struct {
    pthread_t thread_id;        /* unique ID of this thread */
    struct event_base *base;    /* libevent handle this thread uses */
    struct event notify_event;  /* listen event for notify pipe */
    int notify_receive_fd;      /* receiving end of notify pipe */
    int notify_send_fd;         /* sending end of notify pipe */
    struct conn_queue *new_conn_queue; /* queue of new connections to handle */
} LIBEVENT_THREAD;

/*
 * Each libevent instance has a wakeup pipe, which other threads
 * can use to signal that they've put a new connection on its queue.
 */
static LIBEVENT_THREAD *threads;

/*
 * Number of worker threads that have finished setting themselves up.
 */
static int init_count = 0;
static pthread_mutex_t init_lock;
static pthread_cond_t init_cond;

static void thread_libevent_process(int fd, short which, void *arg);

static void wait_for_thread_registration(int nthreads) {
    while (init_count < nthreads) {
        pthread_cond_wait(&init_cond, &init_lock);
    }
}

static void register_thread_initialized(void) {
    pthread_mutex_lock(&init_lock);
    init_count++;
    pthread_cond_signal(&init_cond);
    pthread_mutex_unlock(&init_lock);
}

/*
 * Creates a worker thread.
 */
static void create_worker(void *(*func)(void *), void *arg) {
    pthread_t       thread;
    pthread_attr_t  attr;
    int             ret;

    pthread_attr_init(&attr);

    if ((ret = pthread_create(&thread, &attr, func, arg)) != 0) {
        fprintf(stderr, "Can't create thread: %s\n",
                strerror(ret));
        exit(1);
    }
}

/*
 * Set up a thread's information.
 */
static void setup_thread(LIBEVENT_THREAD *me) {
    me->base = event_init();
    if (! me->base) {
        fprintf(stderr, "Can't allocate event base\n");
        exit(1);
    }

    /* Listen for notifications from other threads */
    event_set(&me->notify_event, me->notify_receive_fd,
              EV_READ | EV_PERSIST, thread_libevent_process, me);
    event_base_set(me->base, &me->notify_event);

    if (event_add(&me->notify_event, 0) == -1) {
        fprintf(stderr, "Can't monitor libevent notify pipe\n");
        exit(1);
    }

    me->new_conn_queue = (CQ *)malloc(sizeof(struct conn_queue));
    if (me->new_conn_queue == NULL) {
        perror("Failed to allocate memory for connection queue");
        exit(EXIT_FAILURE);
    }
    cq_init(me->new_conn_queue);
}

/*
 * Worker thread: main event loop
 */
static void *sensor_slave(void *arg)
{
    LIBEVENT_THREAD *me = (LIBEVENT_THREAD *)arg;

    /* Any per-thread setup can happen here; thread_init() will block until
     * all threads have finished initializing.
     */
    init_mysql_for_sensor();


    /* set an indexable thread-specific memory item for the lock type.
     * this could be unnecessary if we pass the conn *c struct through
     * all item_lock calls...
     */
    register_thread_initialized();

    prctl(PR_SET_NAME, "sensor_slave", 0, 0, 0);

    event_base_loop(me->base, 0);

    return NULL;
}

static void parse_sensor_cmd(Conn *c)
{
	DevDesc *dev;

	char *p = c->rbuf;
	char dev_code[DEV_CODE] = {0};
	bool has_person = false;

	if (c->rsize < MSG_SIZE) {
		c->state = CONN_WAITING;
		return;
	}

	while (*p != ':' && p < c->rbuf + MSG_SIZE) {
		p++;
	}
	if (*p != ':') {
		DUMP_LOG("msg from sensor error");
		c->state = CONN_CLOSING;
		return;
	}
	if (*(++p) == '1') {
		has_person = true;
	}
	strncpy(dev_code, c->rbuf, p - c->rbuf);

	dev = find_dev_by_code(dev_code);
	if (!dev) {
		DUMP_LOG("device not register");
		c->state = CONN_CLOSING;
		return;
	}

	if (clock_gettime(CLOCK_MONOTONIC, &dev->client_update)) {
		DUMP_LOG("clock_gettime() error");
	}
	if (has_person) {
		hit_person_from_sensor(dev);
	}

	c->rsize = 0;
	c->state = CONN_WAITING;
}

static void sensor_event_handle(Conn *c)
{
	for (bool stop = false; !stop;) {
		switch (c->state) {
		case CONN_WAITING:
			c->state = CONN_READ;
			stop = true;
			break;
		case CONN_READ:
			read_conn(c);
			break;
		case CONN_PARSE_CMD:
			parse_sensor_cmd(c);
			break;
		case CONN_CLOSING:
			close_conn(c);
			return;
		default:
			close_conn(c);
			DUMP_LOG("!!! fatal error");
			break;
		}
	}
}

/*
 * Processes an incoming "handle a new connection" item. This is called when
 * input arrives on the libevent wakeup pipe.
 */
static void thread_libevent_process(int fd, short which, void *arg) {
    LIBEVENT_THREAD *me = (LIBEVENT_THREAD *)arg;
    CQ_ITEM *item;
    char buf[1];

    if (read(fd, buf, 1) != 1) {
	    DUMP_LOG("read pipe error");
	    return;
    }

    switch (buf[0]) {
    case 'c':
    item = cq_pop(me->new_conn_queue);

    if (NULL != item) {
	Conn *c = alloc_conn(item->sfd, CONN_READ, EV_READ | EV_PERSIST,
			     me->base, sensor_event_handle, me);
        if (c == NULL) {
            close(item->sfd);
        }
        cqi_free(item);
    }
        break;
    }
}

/* Which thread we assigned a connection to most recently. */
static int last_thread = -1;

/*
 * Dispatches a new connection to another thread. This is only ever called
 * from the main thread, either during initialization (for UDP) or because
 * of an incoming connection.
 */
void dispatch_conn_new(int sfd)
{
    CQ_ITEM *item = cqi_new();
    char buf[1];
    int tid = (last_thread + 1) % g_config.worker;

    LIBEVENT_THREAD *thread = threads + tid;

    last_thread = tid;

    item->sfd = sfd;

    cq_push(thread->new_conn_queue, item);

    buf[0] = 'c';
    if (write(thread->notify_send_fd, buf, 1) != 1) {
        DUMP_LOG("Writing to thread notify pipe");
    }
}

int init_sensor_worker()
{
    int         i;

    pthread_mutex_init(&init_lock, NULL);
    pthread_cond_init(&init_cond, NULL);

    pthread_mutex_init(&cqi_freelist_lock, NULL);
    cqi_freelist = NULL;

    threads = (LIBEVENT_THREAD *)calloc(g_config.worker, sizeof(LIBEVENT_THREAD));
    if (! threads) {
        DUMP_LOG("Can't allocate thread descriptors");
	return -1;
    }

    for (i = 0; i < g_config.worker; i++) {
        int fds[2];
        if (pipe(fds)) {
            DUMP_LOG("Can't create notify pipe");
	    return -1;
        }

        threads[i].notify_receive_fd = fds[0];
        threads[i].notify_send_fd = fds[1];

        setup_thread(&threads[i]);
    }

    /* Create threads after we've done all the libevent setup. */
    for (i = 0; i < g_config.worker; i++) {
        create_worker(sensor_slave, &threads[i]);
    }

    /* Wait for all the threads to set themselves up before returning. */
    pthread_mutex_lock(&init_lock);
    wait_for_thread_registration(g_config.worker);
    pthread_mutex_unlock(&init_lock);

    return 0;
}

} // namespace cobaya
