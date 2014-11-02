﻿using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;
using DevExpress.LookAndFeel;

namespace cobaya
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //确保只有一份运行实例
            bool enable_run;
            Mutex mtx = new Mutex(false, "cobaya_client", out enable_run);
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

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            DevExpress.Skins.SkinManager.EnableFormSkins();
            DevExpress.UserSkins.BonusSkins.Register();
            UserLookAndFeel.Default.SetSkinStyle("Caramel");

            Application.Run(new MainFrame());
        }
    }
}