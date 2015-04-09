#ifndef _SENSOR_WORKER_H
#define _SENSOR_WORKER_H

namespace cobaya {

int init_sensor_worker();
void dispatch_conn_new(int sfd);

} // namespace cobaya

#endif /* _SENSOR_WORKER_H */
