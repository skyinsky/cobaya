using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Windows.Forms;

using DeltaVSoft.RCFProto;
using Google;

namespace cobaya
{
    class RpcClient
    {
        private static RcfProtoChannel _channel;
        private static RpcService.Stub _stub;

        public static bool Init()
        {
            try
            {
                if (!DllPathResolver.Resolve())
                {
                    MessageBox.Show("找不到rpc模块，请联系管理员!");
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
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
                return false;
            }

        }

        public static bool GetAdminInfo()
        {
            try
            {
                string auth_key = "admin_*%$~!@#(*&^+_)_cobaya_58932145672103";

                // Create request object.
                MsgAdminReq.Builder req_build;
                req_build = MsgAdminReq.CreateBuilder();
                req_build.SetKey(auth_key);
                MsgAdminReq req;
                req = req_build.Build();

                // Make a synchronous remote call to server.
                _stub.GetAdminInfo(null, req, null);
                MsgAdminRsp rsp = (MsgAdminRsp)_channel.GetResponse();

                Info.ip = rsp.Ip;
                Info.user = rsp.User;
                Info.passwd = rsp.Passwd;
                Info.db = rsp.Db;

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

  
    }
}
