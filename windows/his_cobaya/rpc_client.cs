using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

using DeltaVSoft.RCFProto;
using Google;

namespace cobaya
{
    class RpcClient
    {
        public static bool Init()
        {
            try
            {
                if (!DllPathResolver.Resolve())
                {
                    //MessageBox.Show("找不到rpc模块，请联系管理员!");
                    return false;
                }

                // Initialize RCFProto.
                RCFProto.Init();

                // Create channel.
                _channel = new RcfProtoChannel(new TcpEndpoint(Config.ip, int.Parse(Config.port)));

                // 5s connect timeout.
                _channel.SetConnectTimeoutMs(5 * 1000);

                // 10s remote call timeout.
                _channel.SetRemoteCallTimeoutMs(10 * 1000);

                // Create service stub.
                _stub = new RpcService.Stub(_channel);

                return true;
            }
            catch (Exception)
            {
                //string err = "请联系管理员\n" + e.ToString();

                //MessageBox.Show(err);
                return false;
            }
        }

        public static void SendOrgFlowMsg(string msg)
        {
            try
            {
                // Create request object.
                MsgOrgFlowReq.Builder req_build;
                req_build = MsgOrgFlowReq.CreateBuilder();
                req_build.SetInfo(msg);

                MsgOrgFlowReq req;
                req = req_build.Build();

                  // Make a synchronous remote call to server.
                _stub.SetOrgFlow(null, req, null);
                //MsgOrgFlowRsp rsp = (MsgOrgFlowRsp)_channel.GetResponse();
            }
            catch (Exception)
            {
            }
        }

        private static RcfProtoChannel _channel;
        private static RpcService.Stub _stub;
    }
}
