using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Net;
using System.Net.Sockets;
using MedLib;

namespace MedTool
{
    public static class ConfigInfo
    {
        public static long medser_ip;
        public static int medser_port;
       
        //读取配置文件"medclient"
        public static bool read_ini_config()
        {
            //打开配置文件
            string parentDir = System.IO.Directory.GetCurrentDirectory();
            string inipath = parentDir + "\\medclient.ini";
            iniconfig ini = new iniconfig(inipath);

            //读取medserver配置信息
            string ipstr = ini.ini_read_value("medserver", "ip"); ;
            string portstr = ini.ini_read_value("medserver", "port");

            if (ipstr.Length == 0 || portstr.Length == 0)
                return false;

            IPAddress iptmp;
            if (!IPAddress.TryParse(ipstr, out iptmp))
                return false;

            ConfigInfo.medser_ip = iptmp.Address;
            ConfigInfo.medser_port = int.Parse(portstr);

            return true;
           }
    }
}
