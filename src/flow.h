#ifndef _FLOW_H
#define _FLOW_H

#include <stdint.h>

namespace cobaya {

struct HisDesc;
class MsgFetchFlowRsp;

int load_flow_manager(void);

bool new_flow(const HisDesc *his);
void del_flow(const HisDesc *his);
void del_flow(void *head, uint64_t user_id);
bool hit_flow(void *head, uint64_t user_id);
void get_flow(void *head, MsgFetchFlowRsp *rsp);

void remove_expire_flow();

} // namespace cobaya

#endif /* _FLOW_H */
