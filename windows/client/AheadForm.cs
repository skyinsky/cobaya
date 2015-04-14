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
    public partial class AheadForm : DevExpress.XtraEditors.XtraForm
    {
        public AheadForm()
        {
            InitializeComponent();
        }

        private void oklogin_Click(object sender, EventArgs e)
        {
            bool grant;
            string info = this.userbox.Text;

            if (info == "")
            {
                MessageBox.Show("请输入描述信息");
                return;
            }

            this.splashScreenManager1.ShowWaitForm();
            grant = RpcClient.AheadFlow(info);
            this.splashScreenManager1.CloseWaitForm();

            this.Close();

            if (grant)
            {
                MessageBox.Show("申请成功！");
            }
            else
            {
                MessageBox.Show("申请失败，请联系管理员！");
            }
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}