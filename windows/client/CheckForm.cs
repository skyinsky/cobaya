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
    public partial class CheckForm : DevExpress.XtraEditors.XtraForm
    {
        public string prev_id;
        public string this_id;

        public CheckForm()
        {
            InitializeComponent();
        }

        private void clear_Click(object sender, EventArgs e)
        {
            this.check_show.Visible = false;

            this.userbox.Text = "";
            this.userbox.Focus();
        }

        private void ok_click(object sender, EventArgs e)
        {
            if (userbox.Text.Length != 11)
            {
                this.userbox.Text = "";
                this.userbox.Focus();
                return;
            }

            prev_id = this_id;
            this_id = userbox.Text;

            this.check_show.Visible = true;
        }

        private void CheckForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }
    }
}