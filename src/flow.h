#ifndef _FLOW_H
#define _FLOW_H

#include <stdint.h>
#include <string>

namespace cobaya {

bool new_flow(const char *host, const char *id);
void del_flow(const char *host, const char *id);
bool hit_flow(const char *host, const char *id);

int load_flow_manager(void);

} // namespace cobaya

#endif /* _FLOW_H */
