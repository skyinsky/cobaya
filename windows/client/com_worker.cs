using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace cobaya
{
    class ComWorker
    {
        public ComWorker(Queue<MsgDiscoveryReq> q, SyncEvents e)
        {
            _queue = q;
            _syncEvents = e;
        }

        public void Routine()
        {
            while (!_syncEvents.ExitThreadEvent.WaitOne(0, false))
            {
                try
                {
                    Thread.Sleep(2000);
                    //find_person();
                    lock (((ICollection)_queue).SyncRoot)
                    {
                        //_queue.Enqueue(res);
                        //_syncEvents.NewItemEvent.Set();
                    }
                }
                catch (Exception)
                {

                }
            }
        }

        private void find_person()
        {
            MsgDiscoveryReq.Builder req_build;
            req_build = MsgDiscoveryReq.CreateBuilder();
            req_build.SetHost(Info.host);
            req_build.SetUser(Info.user);
            req_build.SetPerson(true);
            if (Info.check_form.this_id != null)
            {
                req_build.SetId(Info.check_form.this_id);
            }
            if (Info.check_form.prev_id != null)
            {
                req_build.SetPrevId(Info.check_form.prev_id);
                Info.check_form.prev_id = null;
            }

            MsgDiscoveryReq req = req_build.Build();

            lock (((ICollection)_queue).SyncRoot)
            {
                _queue.Enqueue(req);
                _syncEvents.NewItemEvent.Set();
            }
        }


        private Queue<MsgDiscoveryReq> _queue;
        private SyncEvents _syncEvents;
    }
}
