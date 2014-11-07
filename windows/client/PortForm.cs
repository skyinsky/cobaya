using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Linq;
using System.Windows.Forms;
using System.Diagnostics;
using DevExpress.XtraEditors;

namespace cobaya
{
    public partial class PortForm : DevExpress.XtraEditors.XtraForm
    {
        private int _tickSec;

        public PortForm(string msg, int time)
        { 
            string name = "程序将在" + time.ToString() + "秒后退出";

            InitializeComponent();

            _tickSec = time;       
            this.Text = name;
            label1.Text = msg;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (_tickSec == 0)
            {
                Process.GetCurrentProcess().Kill();
            }
            else
            {
                _tickSec--;

                string name = "程序将在" + _tickSec.ToString() + "秒后退出";

                this.Text = name;
            }
        }

        private void PortForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }
    }
}