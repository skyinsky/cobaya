using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading;

namespace cobaya
{
    public partial class Service1 : ServiceBase
    {
        private IpcWorker ipc_worker;
        private Thread ipc_thread;

        private RpcWorker rpc_worker;
        private Thread rpc_thread;

        private Queue<string> queue;
        private SyncEvents sync;

        public Service1()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            //config
            if (!Config.Init("cobaya.ini"))
            {
                //MessageBox.Show("读取配置文件错误，请联系管理员！");
                Process.GetCurrentProcess().Kill();
            }

            //rpc: config
            if (!RpcClient.Init())
            {
                Process.GetCurrentProcess().Kill();
            }

            //queue & events
            queue = new Queue<string>();
            sync = new SyncEvents();

            //ipc thread
            ipc_worker = new IpcWorker(queue, sync);
            ipc_thread = new Thread(ipc_worker.Routine);
            ipc_thread.Name = "ipc";

            //rpc thread
            rpc_worker = new RpcWorker(queue, sync);
            rpc_thread = new Thread(rpc_worker.Routine);
            rpc_thread.Name = "rpc";

            //start thread
            ipc_thread.Start();
            rpc_thread.Start();

            while (!ipc_thread.IsAlive) ;
            while (!rpc_thread.IsAlive) ;
        }

        protected override void OnStop()
        {
            sync.ExitThreadEvent.Set();

            //模拟事件
            ipc_worker.Stop();

            ipc_thread.Join();
            rpc_thread.Join();
        }
    }
}
