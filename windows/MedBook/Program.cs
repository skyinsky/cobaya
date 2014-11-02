using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;
using DevExpress.LookAndFeel;
using MedLib;

namespace MedBook
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            bool enable_run;
            Mutex mtx = new Mutex(false, "香河县人民医院_DoctorEye", out enable_run);
            if (!enable_run)
            {
                MessageBox.Show("已经有一个程序的实例在运行！");
                return;
            }

            bool ini_config = setting.read_ini_config();
            if (ini_config == false)
                return;

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            DevExpress.Skins.SkinManager.EnableFormSkins();
            DevExpress.UserSkins.BonusSkins.Register();
            UserLookAndFeel.Default.SetSkinStyle("Xmas 2008 Blue");

            setting.dlg_login = new login(true);
            Application.Run(setting.dlg_login);
            if (!setting.dlg_login.enable_enter())
                return;
            //开启数据库连接等待窗口
            setting.dlg_login.splashScreenManager1.ShowWaitForm();

            Application.Run(new MainFrame());
        }
    }
}