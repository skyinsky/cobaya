using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.IO.Ports;
using System.Windows.Forms;
using System.Diagnostics;
using System.Timers;
using DevExpress.LookAndFeel;

namespace cobaya
{
    class ComWorker
    {
        private Queue<MsgDiscoveryReq> _queue;
        private SyncEvents _syncEvents;

        private SerialPort _serialPort;
        private UInt32 _hit_person;

        public ComWorker(Queue<MsgDiscoveryReq> q, SyncEvents e)
        {
            _queue = q;
            _syncEvents = e;
            _hit_person = 0;
        }

        public void Routine()
        {
            Thread.Sleep(5000);

            set_serial_port();

            while (!_syncEvents.ExitThreadEvent.WaitOne(0, false))
            {
                try
                {
                    string msg = _serialPort.ReadLine();

                    if (UInt32.Parse(msg) == 1)
                    {
                        _hit_person++;

                        if (_hit_person >= Info.person)
                        {
                            find_person();
                        }
                        else
                        {
                            _hit_person = 0;
                        }
                    }
                }
                catch (InvalidOperationException e)
                {
                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);

                    DevExpress.Skins.SkinManager.EnableFormSkins();
                    DevExpress.UserSkins.BonusSkins.Register();
                    UserLookAndFeel.Default.SetSkinStyle("Caramel");

                    string msg = "传感器未打开，请联系管理员！\n\n" + e.Message;

                    Application.Run(new PortForm(msg, 60));
                }
                catch (TimeoutException e)
                {
                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);

                    DevExpress.Skins.SkinManager.EnableFormSkins();
                    DevExpress.UserSkins.BonusSkins.Register();
                    UserLookAndFeel.Default.SetSkinStyle("Caramel");

                    string msg = "传感器可能中断，请联系管理员！\n\n" + e.Message;

                    Application.Run(new PortForm(msg, 60));
                }
            }
        }

        private void set_serial_port()
        {
            try
            {
                // Create a new SerialPort object with default settings.
                _serialPort = new SerialPort();

                // Allow the user to set the appropriate properties.
                _serialPort.PortName = Config.dev_port;
                _serialPort.BaudRate = 9600;
                _serialPort.Parity = Parity.None;
                _serialPort.DataBits = 8;
                _serialPort.StopBits = StopBits.One;
                _serialPort.Handshake = Handshake.None;

                // Set the read/write timeouts
                _serialPort.ReadTimeout = (int)Info.sensor * 1000;
                //_serialPort.WriteTimeout = 10000;

                _serialPort.Open();
            }
            catch (Exception e)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);

                DevExpress.Skins.SkinManager.EnableFormSkins();
                DevExpress.UserSkins.BonusSkins.Register();
                UserLookAndFeel.Default.SetSkinStyle("Caramel");

                string msg = "传感器设置错误，请联系管理员！\n\n" + e.Message;

                Application.Run(new PortForm(msg, 30));
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

    }
}
