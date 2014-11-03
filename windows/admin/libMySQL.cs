using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using MySQLDriverCS;

namespace cobaya
{
    public static class libMySQL
    {
        public static MySQLConnection db_conn(string server, string dbname, string user, string pass)
        {
            //设置连库信息
            MySQLConnection conn = new MySQLConnection(new MySQLConnectionString(server, dbname, user, pass).AsString);

            //打开数据库
            conn.Open();

            //防止乱码
            MySQLCommand commn = new MySQLCommand("set names gb2312", conn);
            commn.ExecuteNonQuery();

            return conn;
        }

        public static void db_disconn(MySQLConnection conn)
        {
            if (conn == null)
                return;
            conn.Close();
        }

        public static DataTable db_query(MySQLConnection conn, string sql)
        {
            //通过DataAdapter适配器查询
            MySQLDataAdapter mda = new MySQLDataAdapter(sql, conn);

            //查询出的数据是存在DataTable中的，DataTable可以理解成为一个虚拟的表，
            //DataTable中的一行为一条记录，一列为一个数据库字段
            DataTable dt = new DataTable();
            mda.Fill(dt);

            return dt;
        }
    }

    public static class libsql
    {
        public static string sql_get_keshi = "SELECT `科室`.`科室编号`, `科室`.`科室名称` FROM `科室` ORDER BY `科室`.`科室编号` ASC";
        public static string sql_get_shebei = "SELECT `设备`.`设备编号`, `设备`.`名称`, `设备`.`科室编号` FROM `设备` ORDER BY `设备`.`科室编号` ASC";
        public static string sql_get_yisheng = "SELECT `医生`.`医生编号`, `医生`.`姓名`, `医生`.`科室编号` FROM `医生` ORDER BY `医生`.`科室编号` ASC";
    }
}
