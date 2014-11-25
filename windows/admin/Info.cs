using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Collections;
using MySQLDriverCS;

namespace cobaya
{
    class Info
    {
        public static string ip;
        public static string user;
        public static string passwd;
        public static string db;

        public static DataTable tlb_rooms;
        public static DataTable tlb_devs;
        public static DataTable tlb_docts;

        public static MySQLConnection mysql_con;
    }
}
