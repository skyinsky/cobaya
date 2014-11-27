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
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            DevExpress.Skins.SkinManager.EnableFormSkins();
            DevExpress.UserSkins.BonusSkins.Register();
            UserLookAndFeel.Default.SetSkinStyle("Caramel");

            //确保只有一份运行实例
            bool enable_run;
            mtx = new Mutex(false, "cobaya_client", out enable_run);
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
            
            //global form
            Info.login_form = new LoginForm();
            //Info.check_form = new CheckForm();

            //rpc: dev config
            Info.login_form.splashScreenManager1.ShowWaitForm();
            if (!RpcClient.Init())
            {
                return ;
            }
            if (!RpcClient.GetClientInfo())
            {
                return;
            }
            Info.login_form.splashScreenManager1.CloseWaitForm();

            //queue & events
            queue = new Queue<MsgDiscoveryReq>();
            sync = new SyncEvents();

            //com thread
            com_worker = new ComWorker(queue, sync);
            com_thread = new Thread(com_worker.Routine);
            com_thread.Name = "com";

            //rpc thread
            rpc_worker = new RpcWorker(queue, sync);
            rpc_thread = new Thread(rpc_worker.Routine);
            rpc_thread.Name = "rpc";

            //start thread
            com_thread.Start();
            rpc_thread.Start();

            while (!com_thread.IsAlive) ;
            while (!rpc_thread.IsAlive) ;

            Application.Run(new MainFrame(queue, sync));
        }

        private static ComWorker com_worker;
        private static Thread com_thread;

        private static RpcWorker rpc_worker;
        private static Thread rpc_thread;

        private static Queue<MsgDiscoveryReq> queue;
        private static SyncEvents sync;
    }
}