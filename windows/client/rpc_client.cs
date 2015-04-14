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

        private static RcfProtoChannel fetch_channel;
        private static RpcService.Stub fetch_stub;

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

                // Create channel.
                fetch_channel = new RcfProtoChannel(new TcpEndpoint(Config.ip, int.Parse(Config.port)));
                // 5s connect timeout.
                fetch_channel.SetConnectTimeoutMs(5 * 1000);
                // 10s remote call timeout.
                fetch_channel.SetRemoteCallTimeoutMs(10 * 1000);
                // Create service stub.
                fetch_stub = new RpcService.Stub(fetch_channel);

                return true;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
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

                // 5s connect timeout.
                channel.SetConnectTimeoutMs(5 * 1000);

                // 10s remote call timeout.
                channel.SetRemoteCallTimeoutMs(10 * 1000);

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.GetClientInfo(null, req, null);
                MsgClientRsp rsp = (MsgClientRsp)channel.GetResponse();

                Info.host = rsp.Host;
                Info.dev_code = rsp.DevCode;
                Info.fetch = rsp.Fetch;

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

                // 5s connect timeout.
                channel.SetConnectTimeoutMs(5 * 1000);

                // 10s remote call timeout.
                channel.SetRemoteCallTimeoutMs(10 * 1000);

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.LoginSystem(null, req, null);
                MsgLoginRsp rsp = (MsgLoginRsp)channel.GetResponse();

                return rsp.Grant;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
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

                // 5s connect timeout.
                channel.SetConnectTimeoutMs(5 * 1000);

                // 10s remote call timeout.
                channel.SetRemoteCallTimeoutMs(10 * 1000);

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

                // 5s connect timeout.
                channel.SetConnectTimeoutMs(5 * 1000);

                // 10s remote call timeout.
                channel.SetRemoteCallTimeoutMs(10 * 1000);

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.UpdateUser(null, req, null);
                MsgUpdateUserRsp rsp = (MsgUpdateUserRsp)channel.GetResponse();

                return rsp.Grant;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
                return false;
            }
        }

        public static bool CheckFlow(ref MsgCheckFlowReq req)
        {
            try
            {
                // Make a synchronous remote call to server.
                _stub.CheckFlow(null, req, null);
                MsgCheckFlowRsp rsp = (MsgCheckFlowRsp)_channel.GetResponse();

                return rsp.Grant;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
                return false;
            }
        }

        public static bool FetchFlows(out MsgFetchFlowRsp rsp)
        {
            try
            {
                // Create request object.
                MsgFetchFlowReq.Builder req_build;
                req_build = MsgFetchFlowReq.CreateBuilder();
                req_build.SetDevCode(Info.dev_code);
                MsgFetchFlowReq req = req_build.Build();

                // Make a synchronous remote call to server.
                fetch_stub.FetchFlow(null, req, null);
                rsp = (MsgFetchFlowRsp)fetch_channel.GetResponse();

                return true;
            }
            catch (Exception)
            {
                rsp = null;
                return false;
            }
        }

        public static bool FriendFlow(string info)
        {
            try
            {
                // Create request object.
                MsgFriendFlowReq req;
                MsgFriendFlowReq.Builder req_build;
                req_build = MsgFriendFlowReq.CreateBuilder();
                req_build.SetHost(Info.host);
                req_build.SetDevCode(Info.dev_code);
                req_build.SetInfo(info);
                req = req_build.Build();

                // Create channel.
                RcfProtoChannel channel = new RcfProtoChannel(new TcpEndpoint(Config.ip, int.Parse(Config.port)));

                // 5s connect timeout.
                channel.SetConnectTimeoutMs(5 * 1000);

                // 10s remote call timeout.
                channel.SetRemoteCallTimeoutMs(10 * 1000);

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.FriendFlow(null, req, null);
                MsgFriendFlowRsp rsp = (MsgFriendFlowRsp)channel.GetResponse();

                return rsp.Grant;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
                return false;
            }
        }

        public static bool AheadFlow(string info)
        {
            try
            {
                // Create request object.
                MsgAheadFlowReq req;
                MsgAheadFlowReq.Builder req_build;
                req_build = MsgAheadFlowReq.CreateBuilder();
                req_build.SetHost(Info.host);
                req_build.SetDevCode(Info.dev_code);
                req_build.SetInfo(info);
                req = req_build.Build();

                // Create channel.
                RcfProtoChannel channel = new RcfProtoChannel(new TcpEndpoint(Config.ip, int.Parse(Config.port)));

                // 5s connect timeout.
                channel.SetConnectTimeoutMs(5 * 1000);

                // 10s remote call timeout.
                channel.SetRemoteCallTimeoutMs(10 * 1000);

                // Create service stub.
                RpcService.Stub stub = new RpcService.Stub(channel);

                // Make a synchronous remote call to server.
                stub.AheadFlow(null, req, null);
                MsgAheadFlowRsp rsp = (MsgAheadFlowRsp)channel.GetResponse();

                return rsp.Grant;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
                return false;
            }
        }
    }
}
