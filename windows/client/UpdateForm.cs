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
    public partial class UpdateForm : DevExpress.XtraEditors.XtraForm
    {
        public UpdateForm()
        {
            InitializeComponent();
        }

        private void oklogin_Click(object sender, EventArgs e)
        {
            bool grant;
            string user = this.userbox.Text;
            string passwd = this.passbox.Text;
            string newpass1 = this.newPasswd1.Text;
            string newpass2 = this.newPasswd2.Text;

            if (user == "" || passwd == "" || newpass1 == "" || newpass2 == "")
            {
                MessageBox.Show("请输入用户名与密码");
                return;
            }
            if (passwd != Info.passwd || user != Info.user)
            {
                MessageBox.Show("请输入当前登录系统的用户名与密码！");
                this.userbox.Text = "";
                this.passbox.Text = "";
                return;
            }

            Info.login_form.splashScreenManager1.ShowWaitForm();
            grant = RpcClient.UpdateUser(user, newpass1);
            Info.login_form.splashScreenManager1.CloseWaitForm();
            this.Close();

            if (grant)
            {
                Info.passwd = newpass1;
                MessageBox.Show("密码修改成功！");
            }
            else
            {
                MessageBox.Show("密码修改失败，请联系管理员！");
            }
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}