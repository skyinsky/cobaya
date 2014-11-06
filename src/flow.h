#ifndef _FLOW_H
#define _FLOW_H

#include <stdint.h>

namespace cobaya {

int load_flow_manager(void);
int load_flow_monitor(void);

bool new_flow(const char *host, const char *id);
void del_flow(const char *host, const char *id);
bool hit_flow(const char *host, const char *id);

void remove_expire_flow();

} // namespace cobaya

#endif /* _FLOW_H */
