#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/tcp.h>
#include <netdb.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <pthread.h>
#include <event.h>

#include <libtoolkit/completion.h>
#include <libtoolkit/random.h>
#include <libtoolkit/bug.h>
#include <libtoolkit/socket.h>

#include "common.h"
#include "cache.h"
#include "connect.h"

namespace cobaya {

static cache_t *conn_cache;

static void event_handler(int fd, short flags, void *arg)
{
	Conn *conn = (Conn *)arg;

	if (unlikely(conn->sfd != fd)) {
		DUMP_LOG("got ill event fd");
		exit(EXIT_FAILURE);
	}

	conn->cb(conn);
}

Conn* alloc_conn(int sfd, State state,
		 int ev_flags, event_base *base,
		 event_callback cb, void *private_data)
{
	Conn *conn = NULL;

	conn = (Conn *)cache_alloc(conn_cache);
	if (conn == NULL)
		goto out;
	memset(conn, 0, sizeof(*conn));

	conn->sfd = sfd;
	conn->state = state;

	conn->cb = cb;
	conn->private_data = private_data;

	if (unlikely(event_assign(&conn->ev, base, sfd,
				  ev_flags, event_handler,
				  (void *)conn))) {
		DUMP_LOG("event_assign() error");
		goto out_free;
	}
	if (unlikely(event_add(&conn->ev, 0))) {
		DUMP_LOG("event_add() error");
		goto out_free;
	}

out:
	return conn;
out_free:
	cache_free(conn_cache, conn);
	conn = NULL;
	goto out;
}

void close_conn(Conn *conn)
{
	event_del(&conn->ev);
	close(conn->sfd);
	cache_free(conn_cache, conn);
}

/*
 * read as much as we can, handle buffer overflow and connection close.
 * before reading, move the remaining incomplete fragment of a command
 * (if any) to the beginning of the buffer.
 *
 * To protect us from someone flooding a connection with bogus data causing
 * the connection to eat up all available memory, break out and start looking
 * at the data I've got after a number of reallocs...
 */
void read_conn(Conn *c)
{
	int res, avail;
	bool gotdata = false;

	while (1) {
		avail = BUF_DEF_SIZE - c->rsize;

		res = read(c->sfd, c->rbuf + c->rsize, avail);
		if (res > 0) {
			gotdata = true;
			c->rsize += res;
			if (res == avail) {
				continue;
			} else {
				break;
			}
		} else if (res == 0) {
			goto err_out;
		} else {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				break;
			} else {
				DUMP_LOG("read() error");
				goto err_out;
			}
		}
	}

	if (gotdata)
		c->state = CONN_PARSE_CMD;
	else
		c->state = CONN_WAITING;
	return;
err_out:
	c->state = CONN_CLOSING;
}

int init_conns()
{
	conn_cache = cache_create("conn_cache", sizeof(Conn),
				  0, NULL, NULL);
	if (conn_cache == NULL) {
		DUMP_LOG("no memory");
		return -1;
	}
	return 0;
}

} // namespace cobaya
