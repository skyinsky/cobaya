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
using MedLib;

namespace MedTool
{
    public partial class MainFrame : DevExpress.XtraEditors.XtraForm
    {
        public MainFrame mframe;

        private bool mfram_show;

        private System.Timers.Timer timer;
        public delegate void timer_hide();
        public timer_hide hide_delegate;

        public bool login_yes;
        public string login_user;
        public string login_pass;

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
                MessageBox.Show("您已经登录，如果不是您本人，请注销服务后再登录！");
                return;
            }

            setting.dlg_login = new login(false);
            setting.dlg_login.ShowDialog();
            if (!setting.dlg_login.enable_enter())
                return;
            login_yes = true;
            login_user = setting.login_user;
            login_pass = setting.login_pass;
        }

        private void 注销服务_Click(object sender, EventArgs e)
        {
            login_yes = false;
            MessageBox.Show("您已经安全退出服务！");
        }

        private void 查询记录_Click(object sender, EventArgs e)
        {
            if (login_yes == false)
            {
                MessageBox.Show("请先登录服务！");
                return;
            }

            setting.dlg_login = new login(false);
            setting.dlg_login.ShowDialog();
            if (!setting.dlg_login.enable_enter() || login_user != setting.login_user)
            {
                MessageBox.Show("请使用当前登录系统的身份！");
                return;
            }
        }

    }
}