using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Data;
using MySQLDriverCS;

namespace MedLib
{
    public class iniconfig
    {
        public string path;

        public iniconfig(string path)
        {
            this.path = path;
        }

        #region
        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);

        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section, string key, string defVal, StringBuilder retVal, int size, string filePath);
        #endregion

        public void ini_write_value(string section, string key, string iValue)
        {
            WritePrivateProfileString(section, key, iValue, this.path);
        }

        public string ini_read_value(string section, string key)
        {
            StringBuilder temp = new StringBuilder(255);

            int i = GetPrivateProfileString(section, key, "", temp, 255, this.path);
            return temp.ToString();
        }
    }

    public static class setting
    {
        public static login dlg_login;

        public static string db_server;
        public static string db_database;
        public static string login_user;
        public static string login_pass;
        public static MySQLConnection db_conn;

        //public static DateTime dt_begin;
        //public static DateTime dt_end;

        public static DataTable tlb_devs;
        public static DataTable tlb_dots;
        public static DataTable tlb_rooms;

        public static bool read_ini_config()
        {
            string parentDir = System.IO.Directory.GetCurrentDirectory();
            string inipath = parentDir + "\\medspy.ini";
            iniconfig ini = new iniconfig(inipath);

            setting.db_server = ini.ini_read_value("mysqldb", "server");;
            setting.db_database = ini.ini_read_value("mysqldb", "database");

            if (setting.db_server.Length == 0 || setting.db_database.Length == 0)
                return false;
            else
                return true;
        }
    }
}
