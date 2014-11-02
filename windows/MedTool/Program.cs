using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;
using DevExpress.LookAndFeel;
using MedLib;

namespace MedTool
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
            Mutex mtx = new Mutex(false, "香河县人民医院_MedTool", out enable_run);
            if (!enable_run)
            {
                MessageBox.Show("已经有一个程序的实例在运行！");
                return;
            }

            //读取远程服务器（ip, port)
            bool ini_config = ConfigInfo.read_ini_config();
            if (ini_config == false)
            {
                MessageBox.Show("配置文件medclient读取错误！");
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