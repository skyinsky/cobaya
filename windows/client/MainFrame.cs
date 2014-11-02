using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Linq;
using System.Windows.Forms;
using System.Timers;
using System.Threading;
using DevExpress.XtraEditors;

namespace cobaya
{
    public partial class MainFrame : DevExpress.XtraEditors.XtraForm
    {
        public MainFrame mframe;
    
        //UI 图像管理定时器
        private bool mfram_show;
        private System.Timers.Timer timer;
        public delegate void timer_hide();
        public timer_hide hide_delegate;

        public bool login_yes;

        public MainFrame()
        {
            InitializeComponent();

            login_yes = false;

            mfram_show = true;
            hide_delegate = this.Hide;
            timer = new System.Timers.Timer();
            timer.Elapsed += new ElapsedEventHandler(timer_hide_main_frame);
            timer.Interval = 3000;
            timer.Enabled = true;
        }

        private  void timer_hide_main_frame(object sender, ElapsedEventArgs e)
        {
            if (mfram_show == false)
                return;

            if (this.InvokeRequired)
            {
                this.Invoke(this.hide_delegate);
            }
            else
            {
                this.Hide();
            }

            mfram_show = false;
            timer.Enabled = false;
        }

        private void notifyIcon_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (mfram_show == true)
                    return;

                this.WindowState = FormWindowState.Normal;
                this.Show();

                mfram_show = true;
                timer.Enabled = true;
            }
        }

        private void 登录服务_Click(object sender, EventArgs e)
        {
            if (login_yes == true)
            {
                MessageBox.Show("你已经登录，如果不是本人，请注销服务后再登录！");
                return;
            }

            Info.login_form.ShowDialog();
            login_yes = Info.login_form.grant;
        }

        private void 注销服务_Click(object sender, EventArgs e)
        {
            bool grant;
            string user = Info.user;

            if (login_yes == false)
            {
                MessageBox.Show("你还没有登录系统！");
                return;
            }

            login_yes = false;
            Info.user = "未知";

            Info.login_form.splashScreenManager1.ShowWaitForm();
            grant = RpcClient.LogoutSystem(user);
            Info.login_form.splashScreenManager1.CloseWaitForm();
            if (grant)
            {
                MessageBox.Show("你已经安全注销服务！");
            }
            else
            {
                MessageBox.Show("不正常退出服务，请联系管理员！");
            }
        }

        private void 修改密码_Click(object sender, EventArgs e)
        {
            if (login_yes == false)
            {
                MessageBox.Show("你还没有登录系统！");
                return;
            }

            UpdateForm form = new UpdateForm();
            form.ShowDialog();
        }

        private void notifyIcon_MouseMove(object sender, MouseEventArgs e)
        {
            string show = "当前登录用户： " + Info.user;

            this.notifyIcon.BalloonTipText = show;
            this.notifyIcon.Text = show;
        }

    }
}