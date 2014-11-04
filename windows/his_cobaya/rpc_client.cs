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

                return true;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                //MessageBox.Show(err);
                return false;
            }

        }
    }
}
