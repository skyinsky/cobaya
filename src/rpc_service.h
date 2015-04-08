#ifndef _RPC_SERVICE_H
#define _RPC_SERVICE_H

#include <librcfproto/RCFProto.hpp>
#include "protocol/cobaya.pb.h"

namespace cobaya {

using namespace google::protobuf;

class RpcServiceImpl : public RpcService {
public:
	RpcServiceImpl();
	~RpcServiceImpl();

	/*  admin operations */
	void GetAdminInfo(RpcController *ctl, const MsgAdminReq *req,
			  MsgAdminRsp *rsp, Closure *done);
	void ControlSystem(RpcController *ctl, const MsgMonitorReq *req,
			   MsgMonitorRsp *rsp, Closure *done);

	/* client operations */
	void LoginSystem(RpcController *ctl, const MsgLoginReq *req,
			 MsgLoginRsp *rsp, Closure *done);
	void LogoutSystem(RpcController *ctl, const MsgLogoutReq *req,
			  MsgLogoutRsp *rsp, Closure *done);
	void UpdateUser(RpcController *ctl, const MsgUpdateUserReq *req,
			MsgUpdateUserRsp *rsp, Closure *done);
	void GetClientInfo(RpcController *ctl, const MsgClientReq *req,
			   MsgClientRsp *rsp, Closure *done);
	void FetchFlow(RpcController *ctl, const MsgFetchFlowReq *req,
			MsgFetchFlowRsp *rsp, Closure *done);
	void CheckFlow(RpcController *ctl, const MsgCheckFlowReq *req,
			MsgCheckFlowRsp *rsp, Closure *done);

	/* his operations */
	void SetOrgFlow(RpcController *ctl, const MsgOrgFlowReq *req,
			MsgOrgFlowRsp *rsp, Closure *done);
};

} // namespace cobaya

#endif /* _RPC_SERVICE_H */
