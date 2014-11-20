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
    public partial class FlowForm : DevExpress.XtraEditors.XtraForm
    {
        public UserFlow prev_flow;
        public UserFlow this_flow;
        private MsgFetchFlowRsp show_flows;

        public FlowForm()
        {
            InitializeComponent();
        }
    }
}