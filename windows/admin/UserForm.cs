using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Linq;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace cobaya
{
    public partial class UserForm : DevExpress.XtraEditors.XtraForm
    {
        public bool res;

        public UserForm()
        {
            res = false;
            InitializeComponent();

            this.passwd.Enabled = false;
        }

        private void oklogin_Click(object sender, EventArgs e)
        {
            string user = this.userbox.Text;

            if (user == "")
            {
                MessageBox.Show("请输入用户名与密码");
                return;
            }

            if (user == "AA_匿名")
            {
                MessageBox.Show("'AA_匿名' 是系统保留用户名，您无权操作");
                return;
            }

            string sql = "INSERT INTO `用户` VALUES ('"
                + user + "', '" + this.passwd.Text + "', '"
                + "10.10.10.10" + "', '" + DateTime.Now.ToString() + "')";

            splashScreenManager1.ShowWaitForm();

            if (libMySQL.db_update(sql))
            {
                res = true;
                MessageBox.Show("添加用户成功");
            }
            else
            {
                res = false;
                MessageBox.Show("添加用户失败");
            }
            splashScreenManager1.CloseWaitForm();
            this.Close();

        }

        private void cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string user = this.userbox.Text;

            if (user == "")
            {
                MessageBox.Show("请输入用户名与密码");
                return;
            }
            if (user == "AA_匿名")
            {
                MessageBox.Show("'AA_匿名' 是系统保留用户名，您无权操作");
                return;
            }

            string sql = "DELETE FROM `用户` WHERE `姓名` = '" + user + "'";

            splashScreenManager1.ShowWaitForm();

            if (libMySQL.db_update(sql))
            {
                res = true;
                MessageBox.Show("删除用户成功");
            }
            else
            {
                res = false;
                MessageBox.Show("删除用户失败");
            }
            splashScreenManager1.CloseWaitForm();
            this.Close();
        }
    }
}