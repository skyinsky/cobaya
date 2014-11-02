using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;

namespace cobaya
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            //确保只有一份运行实例
            bool enable_run;
            Mutex mtx = new Mutex(false, "香河县人民医院_cobaya_client", out enable_run);
            if (!enable_run)
            {
                MessageBox.Show("已经有一个程序的实例在运行！");
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
            Application.Run(new Form1());
        }
    }
}
