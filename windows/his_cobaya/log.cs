using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Timers;

namespace cobaya
{
    class Log
    {
        private static FileStream _file;
        private static StreamWriter _writer;

        private static Object _thisLock = new Object();
        private static Timer _timer = new Timer();

        private static void OnTimeout(object sender, ElapsedEventArgs e)
        {
            string parentDir;
            string logpath;

            FileStream file;
            StreamWriter writer;

            FileStream sfile;
            StreamWriter swriter;

            parentDir = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
            logpath = parentDir + "\\log\\"
                + DateTime.Now.Year.ToString() + "年"
                + DateTime.Now.Month.ToString() + "月"
                + DateTime.Now.Day.ToString() + "日"
                + DateTime.Now.Hour.ToString() + "时"
                + DateTime.Now.Minute.ToString() + "分"
                + DateTime.Now.Second.ToString() + "秒"
                + ".txt";

            try
            {
                if (File.Exists(logpath))
                {
                    File.Delete(logpath);
                }

                file = new FileStream(logpath, FileMode.OpenOrCreate);
                writer = new StreamWriter(file);

                lock (_thisLock)
                {
                    sfile = _file;
                    swriter = _writer;

                    _file = file;
                    _writer = writer;
                }

                swriter.Close();
                sfile.Close();

                _timer.Elapsed += OnTimeout;
                _timer.Interval = 10 * 24 * 60 * 60 * 1000;
                _timer.Enabled = true;
            }
            catch (Exception)
            {
            }
        }

        public static bool Init()
        {
            string parentDir;
            string logpath;

            parentDir = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
            logpath = parentDir + "\\log\\"
                + DateTime.Now.Year.ToString() + "年"
                + DateTime.Now.Month.ToString() + "月"
                + DateTime.Now.Day.ToString() + "日"
                + DateTime.Now.Hour.ToString() + "时"
                + DateTime.Now.Minute.ToString() + "分"
                + DateTime.Now.Second.ToString() + "秒"
                + ".txt";

            try
            {
                if (File.Exists(logpath))
                {
                    File.Delete(logpath);
                }

                _file = new FileStream(logpath, FileMode.OpenOrCreate);
                _writer = new StreamWriter(_file);

                _timer.Elapsed += OnTimeout;
                _timer.Interval = 10 * 24 * 60 * 60 * 1000;
                _timer.Enabled = true;

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        public static void WriteLog(string msg)
        {
            try
            {
                lock (_thisLock)
                {
                    _writer.Write("{0} {1}: {2}\r\n", DateTime.Now.ToLongDateString(), DateTime.Now.ToLongTimeString(), msg);

                    _writer.Flush();
                }
            }
            catch (Exception)
            {
            }
        }
    }
}
