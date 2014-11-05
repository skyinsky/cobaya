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
    public partial class LoginForm : DevExpress.XtraEditors.XtraForm
    {
        public bool grant;
        public string user;
        public string passwd;

        public LoginForm()
        {
            grant = false;
            InitializeComponent();
        }

        private void oklogin_Click(object sender, EventArgs e)
        {
            user = this.userbox.Text;
            passwd = this.passbox.Text;

            if (user == "" || passwd == "")
            {
                MessageBox.Show("请输入用户名与密码");
                grant = false;
                return;
            }

            this.splashScreenManager1.ShowWaitForm();
            grant = RpcClient.LoginSystem(user, passwd);
            this.splashScreenManager1.CloseWaitForm();

            this.userbox.Text = "";
            this.passbox.Text = "";
            this.Close();

            if (grant)
            {
                Info.user = user;
                Info.passwd = passwd;
                MessageBox.Show("登录成功！");
            }
            else
            {
                //MessageBox.Show("登录失败，请联系管理员！");
            }
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            grant = false;
            this.Close();
        }
    }
}