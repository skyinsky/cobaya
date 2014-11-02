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

                return true;
            }
            catch (Exception)
            {
                return false;
            }

        }

        public static bool GetClientInfo()
        {
            try
            {
                // Create request object.
                MsgClientReq req;
                MsgClientReq.Builder req_build;
                req_build = MsgClientReq.CreateBuilder();
                string strHostName = Dns.GetHostName();
                foreach (IPAddress ip in System.Net.Dns.GetHostAddresses(strHostName))
                {
                    string host = ip.ToString();
                    req_build.AddHosts(host);
                }
                req = req_build.Build();

                // Create channel.
                RcfProtoChannel channel = new RcfProtoChannel(new TcpEndpoint(Config.ip, int.Parse(Config.port)));

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.GetClientInfo(null, req, null);
                MsgClientRsp rsp = (MsgClientRsp)channel.GetResponse();

                Info.host = rsp.Host;
                Info.dev_code = rsp.DevCode;
                Info.heartbeat = rsp.Heartbeat;
                Info.sensor = rsp.Sensor;

                return true;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
                return false;
            }
        }

        public static bool LoginSystem(string user, string passwd)
        {
            try
            {
                // Create request object.
                MsgLoginReq.Builder req_build;
                req_build = MsgLoginReq.CreateBuilder();
                req_build.SetHost(Info.host);
                req_build.SetUser(user);
                req_build.SetPasswd(passwd);
                MsgLoginReq req;
                req = req_build.Build();

                // Create channel.
                RcfProtoChannel channel = new RcfProtoChannel(new TcpEndpoint(Config.ip, int.Parse(Config.port)));

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.LoginSystem(null, req, null);
                MsgLoginRsp rsp = (MsgLoginRsp)channel.GetResponse();

                return rsp.Grant;
            }
            catch (Exception)
            {
                return false;
            }
        }

        public static bool LogoutSystem(string user)
        {
            try
            {
                // Create request object.
                MsgLogoutReq.Builder req_build;
                req_build = MsgLogoutReq.CreateBuilder();
                req_build.SetHost(Info.host);
                req_build.SetUser(user);
                MsgLogoutReq req;
                req = req_build.Build();

                // Create channel.
                RcfProtoChannel channel = new RcfProtoChannel(new TcpEndpoint(Config.ip, int.Parse(Config.port)));

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.LogoutSystem(null, req, null);
                MsgLogoutRsp rsp = (MsgLogoutRsp)channel.GetResponse();

                return rsp.Grant;
            }
            catch (Exception)
            {
                return false;
            }
        }

        public static bool UpdateUser(string user, string passwd)
        {
            try
            {
                // Create request object.
                MsgUpdateUserReq.Builder req_build;
                req_build = MsgUpdateUserReq.CreateBuilder();
                req_build.SetHost(Info.host);
                req_build.SetUser(user);
                req_build.SetPasswd(passwd);
                MsgUpdateUserReq req;
                req = req_build.Build();

                // Create channel.
                RcfProtoChannel channel = new RcfProtoChannel(new TcpEndpoint(Config.ip, int.Parse(Config.port)));

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.UpdateUser(null, req, null);
                MsgUpdateUserRsp rsp = (MsgUpdateUserRsp)channel.GetResponse();

                return rsp.Grant;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
