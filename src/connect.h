#ifndef _CONNECT_H
#define _CONNECT_H

namespace cobaya {

enum State {
	CONN_WAITING,
	CONN_READ,
	CONN_PARSE_CMD,
	CONN_CLOSING,
};

struct Conn;
typedef void (*event_callback)(Conn *conn);

#define BUF_DEF_SIZE	32
#define MSG_SIZE	8	

struct Conn {
	int	sfd;	/* socket fd */
	State	state;	/* current state */
	event	ev;	/* event */

	event_callback cb;
	void *private_data;

	int	rsize;	/* avail bytes */
	char	rbuf[BUF_DEF_SIZE];
};

Conn* alloc_conn(int sfd, State state, int ev_flags,
		 event_base *base, event_callback cb,
		 void *private_data);
void close_conn(Conn *conn);
void read_conn(Conn *conn);

int init_conns();

} // namespace cobaya

#endif /* _CONNECT_H */
