#ifndef _FLOW_H
#define _FLOW_H

#include <stdint.h>

namespace cobaya {

bool new_flow(const char *host, uint32_t num);
void del_flow(uint32_t num);
bool hit_flow(const char *host);

int load_flow_manager(void);

} // namespace cobaya

#endif /* _FLOW_H */
