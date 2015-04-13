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
        private UInt64 prev_id;
        private UInt64 this_id;

        public OKForm(string str, UInt64 previd, UInt64 thisid)
        {            

            InitializeComponent();            
            this.check_show.Visible = true;
            this.check_show.Text = str;
            prev_id = previd;
            this_id = thisid;
        }

        private void clear_Click(object sender, EventArgs e)
        {
            click = false;
            this.Close();
        }

        private void ok_click(object sender, EventArgs e)
        {
            splashScreenManager1.ShowWaitForm();

            MsgCheckFlowReq.Builder req_build;
            req_build = MsgCheckFlowReq.CreateBuilder();
            req_build.SetHost(Info.host);
            req_build.SetDevCode(Info.dev_code);
            req_build.SetUser(Info.user);
            if (prev_id != 0)
            {
                req_build.SetPrevId(prev_id);
            }
            if (this_id == 0)
            {
                click = false;
                splashScreenManager1.CloseWaitForm();
                this.Close();
                
                return;
            }
            req_build.SetId(this_id);
            MsgCheckFlowReq req = req_build.Build();

            bool grant = RpcClient.CheckFlow(ref req);
            if (grant)
            {
                click = true;
            }
            else
            {
                click = false;
            }

            splashScreenManager1.CloseWaitForm();
            this.Close();
        }
    }
}