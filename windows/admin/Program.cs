using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;
using DevExpress.LookAndFeel;

namespace cobaya
{
    static class Program
    {
        private static Mutex mtx;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            MainFrame frame;

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            DevExpress.Skins.SkinManager.EnableFormSkins();
            DevExpress.UserSkins.BonusSkins.Register();
            UserLookAndFeel.Default.SetSkinStyle("Xmas 2008 Blue");

            //确保只有一份运行实例
            bool enable_run;
            mtx = new Mutex(false, "cobaya_admin", out enable_run);
            if (!enable_run)
            {
                MessageBox.Show("已经有一个程序的实例在运行，请查看系统任务栏！");
                return;
            }

            //config
            if (!Config.Init("cobaya.ini"))
            {
                MessageBox.Show("读取配置文件错误，请联系管理员！");
                return;
            }

            frame = new MainFrame();

            //rpc: mysql config
            frame.splashScreenManager1.ShowWaitForm();
            if (!RpcClient.Init())
            {
                return;
            }
            if (!RpcClient.GetAdminInfo())
            {
                return;
            }
            if (!Info.LoadDatabase())
            {
                return;
            }
            if (!frame.InitTreeList())
            {
                return;
            }
            frame.splashScreenManager1.CloseWaitForm();



            //开启数据库连接等待窗口
            //setting.dlg_login.splashScreenManager1.ShowWaitForm();

            Application.Run(frame);
        }
    }
}