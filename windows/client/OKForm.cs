using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Linq;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace cobaya
{
    public partial class OKForm : DevExpress.XtraEditors.XtraForm
    {
        public bool click;

        public OKForm(string str)
        {            

            InitializeComponent();            
            this.check_show.Visible = true;
            this.check_show.Text = str;
        }

        private void clear_Click(object sender, EventArgs e)
        {
            click = false;
            this.Close();
        }

        private void ok_click(object sender, EventArgs e)
        {
            click = true;
            this.Close();
        }
    }
}