#include <sys/types.h>
#include <sys/socket.h>
#include <sys/prctl.h>

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
#include "rpc.h"
#include "config.h"
#include "flow.h"
#include "main.h"
#include "connect.h"
#include "sensor_server.h"
#include "sensor_worker.h"

namespace cobaya {

static struct event ev_listen;
static struct event_base *ev_base;
static pthread_t thread_id;

static void handle_accept(int fd, short flags, void *arg)
{
	int sfd;

retry:
	sfd = accept(fd, NULL, NULL);
	if (sfd == -1) {
		if (errno == EINTR) {
			goto retry;
		}

		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			goto out;
		}

		DUMP_LOG("accept error: %d", errno);
		goto out;
	}

	if (set_nonblocking(sfd)) {
		close(sfd);
		DUMP_LOG("set nonblocking error");
		goto out;
	}

	DUMP_DEBUG("new connect fd: %d", sfd);

	dispatch_conn_new(sfd);

out:
	return;
}

static int start_listen(int rcvbuf, int backlog)
{
	int err = 0, sfd;
	sockinfo si;

	err = resolve_addr(g_config.rpc_ip, g_config.rpc_sport, &si);
	if (err) {
		DUMP_LOG("resolve address error");
		goto out;
	}

	sfd = socket(si.family, SOCK_STREAM, 0);
	if (sfd == -1) {
		DUMP_LOG("socket error");
		err = -1;
		goto out;
	}

	if (set_nonblocking(sfd)) {
		DUMP_LOG("set nonblocking error");
	}

	if (set_reuseaddr(sfd)) {
		DUMP_LOG("set reuseaddr error");
	}

	if (set_keepalive(sfd)) {
		DUMP_LOG("set keepalive error");
	}

	if (set_linger(sfd, 0, 0)) {
		DUMP_LOG("set linger error");
	}

	if (set_tcpnodelay(sfd)) {
		DUMP_LOG("set tcpnodelay error");
	}

	if (set_rcvbuf(sfd, rcvbuf)) {
		DUMP_LOG("set rcvbuf size error");
	}

	err = bind(sfd, (sockaddr *)&si.addr, si.addrlen);
	if (err == -1) {
		DUMP_LOG("bind error");
		close(sfd);
		goto out;
	}

	err = listen(sfd, backlog);
	if (err == -1) {
		DUMP_LOG("listen error");
		close(sfd);
		goto out;
	}

	if (event_assign(&ev_listen, ev_base, sfd,
			 EV_READ | EV_PERSIST,
			 handle_accept, NULL)) {
		close(sfd);
		err = -1;
		DUMP_LOG("event_assign error");
		goto out;
	}

	if (event_add(&ev_listen, 0)) {
		close(sfd);
		err = -1;
		DUMP_LOG("event_add error");
	}

out:
	return err;
}

void* sensor_master(void *arg)
{
	completion *work = (completion *)arg;

	/* init slaves */
	if (init_sensor_worker()) {
		DUMP_LOG("init sensor workers error");
		exit(EXIT_FAILURE);
	}

	/* init server */
	ev_base = event_base_new();
	if (ev_base == NULL) {
		DUMP_LOG("alloc event base error");
		exit(EXIT_FAILURE);
	}
	if (init_conns()) {
		DUMP_LOG("init conns cache error");
		exit(EXIT_FAILURE);
	}
	if (start_listen(4096, 1024)) {
		DUMP_LOG("start listen socket error");
		exit(EXIT_FAILURE);
	}

	prctl(PR_SET_NAME, "sensor_master", 0, 0, 0);

	/* notify father */
	complete(work);

	event_base_loop(ev_base, 0);

	DUMP_LOG("******************** stop listen socket ********************");

	return NULL;
}

int start_sensor_server()
{
	int err;
	DECLARE_COMPLETION(work);
	void *arg = &work;

	err = pthread_create(&thread_id, NULL,
			     sensor_master, arg);
	if (err != 0) {
		DUMP_LOG("start scheduler error");
		return -1;
	}
	wait_for_completion(&work);

	return 0;
}

} // namespace cobaya
