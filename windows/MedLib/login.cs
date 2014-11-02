using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Linq;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using MySQLDriverCS;

namespace MedLib
{
    public partial class login : DevExpress.XtraEditors.XtraForm
    {
        private bool enable;
        private bool root;

        public login(bool root)
        {
            this.root = root;
            enable = false;
            InitializeComponent();
        }

        public bool enable_enter()
        {
            return enable;
        }

        private void oklogin_Click(object sender, EventArgs e)
        {
            string user = this.userbox.Text;
            string pass = this.passbox.Text;
            MySQLConnection conn = null;
            DataTable db;
            string sql = "SELECT DISTINCT `医生`.`权限` FROM `医生` WHERE `医生`.`姓名` =  '" + user + "\'";

            try
            {
                conn = libMySQL.db_conn(setting.db_server, setting.db_database, user, pass);
                db = libMySQL.db_query(conn, sql);

                if (db.Rows.Count != 1)
                {
                    MessageBox.Show("用户名或密码错误");

                    goto clear;
                }
                if (this.root && int.Parse(db.Rows[0]["权限"].ToString()) != 3)
                {
                    MessageBox.Show("无权限登录");

                    goto clear;
                }

                enable = true;
                setting.login_user = user;
                setting.login_pass = pass;
                this.Close();
                return;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                goto clear;
            }
            finally
            {
                libMySQL.db_disconn(conn);
            }

        clear:
            this.userbox.Clear();
            this.passbox.Clear();
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            this.Close();

            enable = false;
        }
    }
}