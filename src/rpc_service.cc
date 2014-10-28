#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "rpc_service.h"

namespace cobaya {

bool g_start_monitor = false;

void RpcServiceImpl::GetAdminInfo(RpcController *ctl,
				  const MsgAdminReq *req,
				  MsgAdminRsp *rsp, Closure *done)
{

}

void RpcServiceImpl::ControlSystem(RpcController *ctl,
				   const MsgMonitorReq *req,
				   MsgMonitorRsp *rsp, Closure *done)
{
	if (!strcmp(AUTH_KEY, req->key().c_str())) {
		g_start_monitor = req->start();
	}

	rsp->set_status(true);

	/* Send response back to the client */
	done->Run();
}

void RpcServiceImpl::GetClientInfo(RpcController *ctl,
				   const MsgClientReq *req,
				   MsgClientRsp *rsp, Closure *done)
{

}

void RpcServiceImpl::AppendInfo(RpcController *ctl,
				const MsgDiscoveryReq *req,
				MsgDiscoveryRsp *rsp, Closure *done)
{

}

void RpcServiceImpl::RegisterUser(RpcController *ctl,
				  const MsgRegUserReq *req,
				  MsgRegUserRsp *rsp, Closure *done)
{

}

void RpcServiceImpl::LoginSystem(RpcController *ctl,
				 const MsgLoginReq *req,
				 MsgLoginRsp *rsp, Closure *done)
{

}

void RpcServiceImpl::LogoutSystem(RpcController *ctl,
				  const MsgLogoutReq *req,
				  MsgLogoutRsp *rsp, Closure *done)
{

}

void RpcServiceImpl::StartFlow(RpcController *ctl,
			       const MsgStartReq *req,
			       MsgStartRsp *rsp, Closure *done)
{

}

void RpcServiceImpl::StopFlow(RpcController *ctl,
			      const MsgStopReq *req,
			      MsgStopRsp *rsp, Closure *done)
{

}







} // namespace cobaya
