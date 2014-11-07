using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace cobaya
{
    class Config
    {
        public static string ip;
        public static string port;

        public static string dev_port;

        private static string path;

        #region
        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);

        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section, string key, string defVal, StringBuilder retVal, int size, string filePath);
        #endregion

        private static string Read(string section, string key)
        {
            StringBuilder temp = new StringBuilder(255);

            int i = GetPrivateProfileString(section, key, "", temp, 255, path);
            return temp.ToString();
        }

        public static bool Init(string ini)
        {
            string parentDir;
            string inipath;

            parentDir = System.IO.Directory.GetCurrentDirectory();
            inipath = parentDir + "\\" + ini;

            Config.path = inipath;
            Config.ip = Read("server", "ip");
            Config.port = Read("server", "port");
            Config.dev_port = Read("device", "port");

            if (Config.ip == "" || Config.port == "" || Config.dev_port == "")
            {
                return false;
            }
            {
                return true;
            }


        }
    }
}
