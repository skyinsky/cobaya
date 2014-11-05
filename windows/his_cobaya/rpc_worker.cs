using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace cobaya
{
    class RpcWorker
    {
        public RpcWorker(Queue<string> q, SyncEvents e)
        {
            _queue = q;
            _syncEvents = e;
        }

        public void Routine()
        {
            while (WaitHandle.WaitAny(_syncEvents.EventArray) != 1)
            {
                try
                {
                    for (; ;)
                    {
                        string msg = null;

                        lock (((ICollection)_queue).SyncRoot)
                        {
                            if (_queue.Count == 0)
                                break;
                            msg = _queue.Dequeue();
                        }

                        if (msg != null)
                            RpcClient.SendOrgFlowMsg(msg);
                    }
                }
                catch (Exception)
                {
                }
            }
        }

        private Queue<string> _queue;
        private SyncEvents _syncEvents;
    }
}
