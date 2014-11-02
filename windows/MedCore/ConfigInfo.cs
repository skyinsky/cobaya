using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Net;
using System.Net.Sockets;
using MedLib;

namespace MedCore
{
    public static class ConfigInfo
    {
        public static long medser_ip;
        public static int medser_port;

        public static long meddb_server;
        public static string meddb_name;

        private static bool read_medser(iniconfig ini)
        {
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

        private static bool read_meddb(iniconfig ini)
        {
            //读取medserver配置信息
            string dbser = ini.ini_read_value("meddb", "server"); ;
            string dbname = ini.ini_read_value("meddb", "database");

            if (dbser.Length == 0 || dbname.Length == 0)
                return false;

            IPAddress iptmp;
            if (!IPAddress.TryParse(dbser, out iptmp))
                return false;

            ConfigInfo.meddb_server = iptmp.Address;
            ConfigInfo.meddb_name = dbname;

            return true;
        }

        //读取配置文件"medserver"
        public static bool read_ini_config()
        {
            //打开配置文件
            string parentDir = System.IO.Directory.GetCurrentDirectory();
            string inipath = parentDir + "\\medserver.ini";
            iniconfig ini = new iniconfig(inipath);

            if (!read_medser(ini) || !read_meddb(ini))
                return false;
            else
                return true;
           }
    }
}
