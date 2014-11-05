using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;

namespace cobaya
{
    class IpcWorker
    {
        public IpcWorker(Queue<string> q, SyncEvents e)
        {
            _queue = q;
            _syncEvents = e;

            _pipe = new NamedPipeServerStream("cobaya_his_pipe");
            _reader = new StreamReader(_pipe);
        }

        public void Routine()
        {
            while (!_syncEvents.ExitThreadEvent.WaitOne(0, false))
            {
                try
                {
                    if (!_pipe.IsConnected)
                    {
                        _pipe.WaitForConnection();
                    }

                    string res = _reader.ReadLine();
                    if (res == null)
                        continue;

                    lock (((ICollection)_queue).SyncRoot)
                    {
                        _queue.Enqueue(res);
                        _syncEvents.NewItemEvent.Set();
                    }
                }
                catch (Exception)
                {
                    _pipe.Close();
                    _pipe = new NamedPipeServerStream("cobaya_his_pipe");
                    _reader = new StreamReader(_pipe);
                }
            }
        }

        public void Stop()
        {
            try
            {
                if (_pipe.IsConnected)
                {
                    Process.GetCurrentProcess().Kill();
                }
                else
                {
                    NamedPipeClientStream pipe = new NamedPipeClientStream("cobaya_his_pipe");
                    StreamWriter writer = new StreamWriter(pipe);

                    pipe.Connect();

                    writer.WriteLine("");
                    writer.Flush();
                }
            }
            catch (Exception)
            {
            }
        }

        private Queue<string> _queue;
        private SyncEvents _syncEvents;

        private NamedPipeServerStream _pipe;
        private StreamReader _reader;
    }
}
