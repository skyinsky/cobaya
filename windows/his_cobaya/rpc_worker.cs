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
                        lock (((ICollection)_queue).SyncRoot)
                        {
                            if (_queue.Count == 0)
                                break;
                            string res = _queue.Dequeue();
                        }
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
