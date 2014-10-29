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
	void GetClientInfo(RpcController *ctl, const MsgClientReq *req,
			   MsgClientRsp *rsp, Closure *done);
	void UpdateUser(RpcController *ctl, const MsgUpdateUserReq *req,
			MsgUpdateUserRsp *rsp, Closure *done);
	void LoginSystem(RpcController *ctl, const MsgLoginReq *req,
			 MsgLoginRsp *rsp, Closure *done);
	void LogoutSystem(RpcController *ctl, const MsgLogoutReq *req,
			  MsgLogoutRsp *rsp, Closure *done);
	void AppendInfo(RpcController *ctl, const MsgDiscoveryReq *req,
			MsgDiscoveryRsp *rsp, Closure *done);

	/* his operations */
	void StartFlow(RpcController *ctl, const MsgStartReq *req,
		       MsgStartRsp *rsp, Closure *done);
	void StopFlow(RpcController *ctl, const MsgStopReq *req,
		      MsgStopRsp *rsp, Closure *done);
};

} // namespace cobaya

#endif /* _RPC_SERVICE_H */
