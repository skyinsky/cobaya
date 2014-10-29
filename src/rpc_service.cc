#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "common.h"
#include "config.h"
#include "dev.h"
#include "office.h"
#include "user.h"
#include "flow.h"
#include "rpc.h"
#include "rpc_service.h"
#include "mysql_wrapper.h"

namespace cobaya {

using namespace RCF;

bool g_start_monitor = false;

RpcServiceImpl::RpcServiceImpl()
{

}

RpcServiceImpl::~RpcServiceImpl()
{

}

void RpcServiceImpl::GetAdminInfo(RpcController *ctl,
				  const MsgAdminReq *req,
				  MsgAdminRsp *rsp, Closure *done)
{
	if (strcmp(AUTH_KEY, req->key().c_str())) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("not allowed");
	} else {
		rsp->set_ip(g_config.mysql_ip);
		rsp->set_user(g_config.mysql_user);
		rsp->set_passwd(g_config.mysql_passwd);
		rsp->set_db(g_config.mysql_db);
	}

	done->Run();
}

void RpcServiceImpl::ControlSystem(RpcController *ctl,
				   const MsgMonitorReq *req,
				   MsgMonitorRsp *rsp, Closure *done)
{
	if (strcmp(AUTH_KEY, req->key().c_str())) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("not allowed");
	} else {
		rsp->set_status(true);
		g_start_monitor = req->start();
	}

	/* Send response back to the client */
	done->Run();
}

void RpcServiceImpl::GetClientInfo(RpcController *ctl,
				   const MsgClientReq *req,
				   MsgClientRsp *rsp, Closure *done)
{
	DevDesc *dev = NULL;

	int sz = req->hosts_size();
	for (int i = 0; i < sz; i++) {
		dev = find_dev_by_host(req->hosts(i).c_str());
		if (dev != NULL) {
			break;
		}
	}

	if (dev == NULL) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("host not register");
	} else {
		rsp->set_host(dev->host);
		rsp->set_dev_code(dev->code);
		rsp->set_heartbeat(g_config.client_heartbeat);
		rsp->set_sensor(g_config.client_sensor);

//		for (OfficeDesc *desc = office_head.next;
//		     desc != &office_head; desc = desc->next) {
//			rsp->add_office(desc->name);
//		}
	}

	done->Run();
}

void RpcServiceImpl::UpdateUser(RpcController *ctl,
				const MsgUpdateUserReq *req,
				MsgUpdateUserRsp *rsp, Closure *done)
{
	if (update_user(req->user().c_str(),
			req->passwd().c_str(),
			req->host().c_str())) {
		rsp->set_grant(false);
	} else {
		rsp->set_grant(true);
	}

	done->Run();
}

void RpcServiceImpl::LoginSystem(RpcController *ctl,
				 const MsgLoginReq *req,
				 MsgLoginRsp *rsp, Closure *done)
{
	if (logon_client(req->user().c_str(),
			 req->passwd().c_str(),
			 req->host().c_str())) {
		rsp->set_grant(false);
	} else {
		rsp->set_grant(true);
	}

	done->Run();
}

void RpcServiceImpl::LogoutSystem(RpcController *ctl,
				  const MsgLogoutReq *req,
				  MsgLogoutRsp *rsp, Closure *done)
{
	if (logout_client(req->user().c_str())) {
		rsp->set_grant(false);
	} else {
		rsp->set_grant(true);
	}

	done->Run();
}

static void store_doubt_flow(DevDesc *dev, const MsgDiscoveryReq *req)
{
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char sql[512] = {0};

	if (gettimeofday(&now, NULL)) {
		DUMP_LOG("gettimeofday() error");
		return;
	}
	date = localtime(&now.tv_sec);
	if (date == NULL) {
		DUMP_LOG("localtime() error");
		return;
	}
	strftime(datetmp, 128, "%F %T", date);

	sprintf(sql, "INSERT INTO `日志` VALUES ('%s', '%s', '%s', '%s', '%s', '%s')",
		req->user().c_str(), req->host().c_str(), datetmp,
		dev->code, dev->name, dev->office);
	if (mysql->ModifyQuery(sql)) {
		DUMP_LOG("insert log table (user:%s) error", req->user().c_str());
	}
}

void RpcServiceImpl::AppendInfo(RpcController *ctl,
				const MsgDiscoveryReq *req,
				MsgDiscoveryRsp *rsp, Closure *done)
{
	DevDesc *dev;

	dev = find_dev_by_host(req->host().c_str());
	if (dev == NULL) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("host not register");
		goto out;
	} else {
		/* update alive heartbeat */
		if (clock_gettime(CLOCK_MONOTONIC, &dev->client_update)) {
			DUMP_LOG("clock_gettime() error");
		}
	}

	if (req->person() && !hit_flow(req->host().c_str())) {
		store_doubt_flow(dev, req);
		rsp->set_grant(false);
	} else {
		rsp->set_grant(true);
	}

out:	done->Run();

}

void RpcServiceImpl::StartFlow(RpcController *ctl,
			       const MsgStartReq *req,
			       MsgStartRsp *rsp, Closure *done)
{
	if (!new_flow(req->check_host().c_str(), req->unique_num())) {
		DUMP_LOG("not good!!!");
		exit(EXIT_FAILURE);
	}

	rsp->set_status(1);

	done->Run();
}

void RpcServiceImpl::StopFlow(RpcController *ctl,
			      const MsgStopReq *req,
			      MsgStopRsp *rsp, Closure *done)
{
	del_flow(req->unique_num());

	rsp->set_status(1);

	done->Run();
}







} // namespace cobaya
