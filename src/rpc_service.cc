#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "common.h"
#include "config.h"
#include "dev.h"
#include "office.h"
#include "user.h"
#include "flow.h"
#include "main.h"
#include "rpc.h"
#include "rpc_service.h"
#include "mysql_wrapper.h"
#include "his.h"

namespace cobaya {

using namespace RCF;

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
		rsp->set_ip(g_config.mysql_remote_ip);
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
	DevDesc *dev;

	if (logon_client(req->user().c_str(),
			 req->passwd().c_str(),
			 req->host().c_str())) {
		rsp->set_grant(false);
		goto out;
	} else {
		rsp->set_grant(true);
	}

	dev = find_dev_by_host(req->host().c_str());
	if (dev == NULL) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("host not register");
		goto out;
	}
	strcpy(dev->doct_name, req->user().c_str());

out:
	done->Run();
}

void RpcServiceImpl::LogoutSystem(RpcController *ctl,
				  const MsgLogoutReq *req,
				  MsgLogoutRsp *rsp, Closure *done)
{
	DevDesc *dev;

	if (logout_client(req->user().c_str())) {
		rsp->set_grant(false);
		goto out;
	} else {
		rsp->set_grant(true);
	}

	dev = find_dev_by_host(req->host().c_str());
	if (dev == NULL) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("host not register");
		goto out;
	}
	strcpy(dev->doct_name, "AA_匿名");

out:

	done->Run();
}

void RpcServiceImpl::CheckFlow(RpcController *ctl, const MsgCheckFlowReq *req,
			       MsgCheckFlowRsp *rsp, Closure *done)
{
	DevDesc *dev;

	dev = find_dev_by_code(req->dev_code().c_str());
	if (dev == NULL) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("host not register");
		goto out;
	}

	if (req->has_prev_id()) {
		del_flow(dev->head, req->prev_id());
	}

	if (dev->check_flow) {
		Timer::SchedCancel(&dev->check_timer);
	}

	if (!hit_flow(dev->head, req->id())) {
		DUMP_LOG("not register user id: %llu", req->id());
		rsp->set_grant(false);
		dev->check_flow = false;
	} else {
		rsp->set_grant(true);
		dev->check_flow = true;
		dev->sensor_last = 0;
		Timer::SchedOneshot(&dev->check_timer);
	}

out:	done->Run();
}

static void store_friend_flow(DevDesc *dev, const char *info)
{
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char tmp[512] = {0};

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

	sprintf(tmp, "INSERT INTO `亲属` VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
		dev->code, dev->name, dev->host,
		dev->office_id, dev->office_name, dev->office_owner, datetmp,
		dev->doct_name, info);
	if (main_mysql->ModifyQuery(tmp)) {
		DUMP_LOG("insert value error");
	}
}

void RpcServiceImpl::FriendFlow(RpcController *ctl,
				const MsgFriendFlowReq *req,
				MsgFriendFlowRsp *rsp, Closure *done)
{
	DevDesc *dev;

	dev = find_dev_by_code(req->dev_code().c_str());
	if (dev == NULL) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("host not register");
		goto out;
	}
	if (dev->check_flow) {
		Timer::SchedCancel(&dev->check_timer);
	}

	store_friend_flow(dev, req->info().c_str());

	dev->check_flow = true;
	dev->sensor_last = 0;
	Timer::SchedOneshot(&dev->check_timer);

	rsp->set_grant(true);
out:
	done->Run();
}

static void store_ahead_flow(DevDesc *dev, const char *info)
{
	struct tm *date;
	struct timeval now;
	char datetmp[128] = {0};
	char tmp[512] = {0};

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

	sprintf(tmp, "INSERT INTO `紧急` VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
		dev->code, dev->name, dev->host,
		dev->office_id, dev->office_name, dev->office_owner, datetmp,
		dev->doct_name, info);
	if (main_mysql->ModifyQuery(tmp)) {
		DUMP_LOG("insert value error");
	}
}

void RpcServiceImpl::AheadFlow(RpcController *ctl,
			       const MsgAheadFlowReq *req,
			       MsgAheadFlowRsp *rsp, Closure *done)
{
	DevDesc *dev;

	dev = find_dev_by_code(req->dev_code().c_str());
	if (dev == NULL) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("host not register");
		goto out;
	}
	if (dev->check_flow) {
		Timer::SchedCancel(&dev->check_timer);
	}

	store_ahead_flow(dev, req->info().c_str());

	dev->check_flow = true;
	dev->sensor_last = 0;
	Timer::SchedOneshot(&dev->check_timer);

	rsp->set_grant(true);
out:
	done->Run();
}

void RpcServiceImpl::FetchFlow(RpcController *ctl,
			       const MsgFetchFlowReq *req,
			       MsgFetchFlowRsp *rsp, Closure *done)
{
	DevDesc *dev;

	dev = find_dev_by_code(req->dev_code().c_str());
	if (dev == NULL) {
		RcfProtoController *rcfctl = (RcfProtoController *)ctl;

		rcfctl->SetFailed("host not register");
		goto out;
	}

	get_flow(dev->head, rsp);

out:	done->Run();
}

void RpcServiceImpl::SetOrgFlow(RpcController *ctl,
				const MsgOrgFlowReq *req,
				MsgOrgFlowRsp *rsp, Closure *done)
{
	int res;
	int add;
	int len, f = 0, s = 0, t = 0, e = 0, count = 0;
	char *p;
	HisDesc his;

	memset(&his, 0, sizeof(his));

	p = (char *)req->info().c_str();
	len = strlen(req->info().c_str());
	for (int i = 0; i < len; i++) {
		if (*(p + i) == ':')
			count++;
		if (count == 2 && f == 0) {
			f = i + 1;
			continue;
		}
		if (count == 3 && s == 0) {
			s = i + 1;
			continue;
		}
		if (count == 4 && t == 0) {
			t = i + 1;
			continue;
		}
		if (count == 5 && e == 0) {
			e = i;
			continue;
		}
	}
	if (count != 7) {
		goto err;
	}

	strncpy((char *)&his.apply_id, p + f, s - f - 1);
	strncpy((char *)&his.user, p + s, t - s - 1);
	strncpy((char *)&his.item_name, p + t, e - t);

	res = sscanf(p, "%lu:%d",
		     &his.user_id, &add);
	if (res != 2)
		goto err;
	
	res = sscanf(p + e + 1, "%d:%d:%s",
		     &his.exe_office_id,
		     &his.app_office_id, (char *)&his.doctor);
	if (res != 3)
		goto err;
	//DUMP_LOG("user: %s, doctor: %s", his.user, his.doctor);

	if (add) {
		new_flow(&his);
	} else {
		del_flow(&his);
	}
	rsp->set_status(1);

out:
	done->Run();
	return;

err:
	DUMP_LOG("his数据格式错误, %s", req->info().c_str());
	rsp->set_status(0);
	goto out;
}


} // namespace cobaya

