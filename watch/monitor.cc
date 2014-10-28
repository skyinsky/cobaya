#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <libiniparser/iniparser.h>
#include <librcfproto/RCFProto.hpp>
#include "protocol/cobaya.pb.h"
#include "common.h"
#include "monitor.h"
#include "config.h"

namespace cobaya {

using namespace RCF;
using namespace google::protobuf;

void send_start_msg()
{
	try {
		/* Initialize RCFProto */
		RCF::init();

		/* Create MsgMonitorReq object */
		MsgMonitorReq req;
		req.set_key(AUTH_KEY);
		req.set_start(true);

		/* Create response object */
		MsgMonitorRsp rsp;

		/* Create channel */
		RcfProtoChannel channel(TcpEndpoint(g_config.rpc_ip,
					g_config.rpc_port));

		/* Create service stub */
		RpcService::Stub stub(&channel);

		/* Make a synchronous remote call to server */
		stub.ControlSystem(NULL, &req, &rsp, NULL);

	} catch (const RCF::Exception &e) {
		DUMP_LOG("%s", e.getErrorString().c_str());
		exit(EXIT_FAILURE);
	}
}

int load_start_time(const char *path)
{
	int ret = 0;
	dictionary *ini;

	ini = iniparser_load(path);
	if (ini == NULL) {
		DUMP_LOG("load %s error", path);
		return 1;
	}

	ret = iniparser_getint(ini, "monitor:start_sys", 1);

	iniparser_freedict(ini);

	return ret;
}

void start_cobaya_sys()
{
	int time;

	time = load_start_time("cobaya.ini");

	if (sleep(time)) {
		DUMP_LOG("sleep() error");
		exit(EXIT_FAILURE);
	}

	send_start_msg();
}

void monitor_loop()
{
	pid_t pid;

run_loop:
	pid = fork();

	if (pid == -1) {
		DUMP_LOG("fork failed");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		char *const argv[] = { "cobaya", NULL };
		char *const envp[] = { NULL };
		
		execve("cobaya", argv, envp);
		DUMP_LOG("execve() error");
	} else {
		int status;

		//start_cobaya_sys();
		waitpid(pid, &status, 0);

		DUMP_LOG("child process exit");
		goto run_loop;
	}
}

} // namespace cobaya
