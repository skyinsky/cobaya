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
        public RpcWorker(Queue<MsgDiscoveryReq> q, SyncEvents e)
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
                        MsgDiscoveryReq req = null;

                        lock (((ICollection)_queue).SyncRoot)
                        {
                            if (_queue.Count == 0)
                                break;
                            req = _queue.Dequeue();
                        }

                        if (req != null)
                            RpcClient.AppendInfo(ref req);
                    }
                }
                catch (Exception)
                {
                }
            }
        }

        private Queue<MsgDiscoveryReq> _queue;
        private SyncEvents _syncEvents;
    }
}
