using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Collections;
using System.Windows;
using System.Windows.Forms;
using MySQLDriverCS;

namespace cobaya
{
    class Info
    {
        public static string ip;
        public static string user;
        public static string passwd;
        public static string db;

        //public static DataTable tlb_office;
        public static DataTable tlb_user;
        public static DataTable tlb_dev;

        public static MySQLConnection mysql_con;

        public static bool LoadDatabase()
        {
            try
            {
                mysql_con = libMySQL.db_conn(ip, db, user, passwd);

                Load_dev();
                Load_user();
                //Load_office();

                return true;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);
                return false;
            }
        }

        //private static void Load_office()
        //{
        //    string sql = "SELECT * FROM `监控科室`";

        //    tlb_office = libMySQL.db_query(mysql_con, sql);
        //}

        private static void Load_user()
        {
            string sql = "SELECT * FROM `用户`";

            tlb_user = libMySQL.db_query(mysql_con, sql);
        }

        private static void Load_dev()
        {
            string sql = "SELECT * FROM `设备`";

            tlb_dev = libMySQL.db_query(mysql_con, sql);
        }
    }
}
