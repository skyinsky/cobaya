using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Linq;
using System.Timers;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using DevExpress.XtraGrid;
using DevExpress.XtraGrid.Views.Grid;
using DevExpress.XtraGrid.Views.Grid.ViewInfo;
using DevExpress.Utils;

namespace cobaya
{
    public partial class FlowForm : DevExpress.XtraEditors.XtraForm
    {
        public UInt64 prev_id;
        public UInt64 this_id;
        public DataRow prev_row;
        public DataRow this_row;

        public MsgFetchFlowRsp show_flow;

        private System.Timers.Timer timer;

        public delegate void reload_flows(DataTable dt);
        public reload_flows reload;

        public FlowForm()
        {
            InitializeComponent();

            timer = new System.Timers.Timer(Info.fetch * 1000);
            timer.Elapsed += OnTimedEvent;
            timer.Enabled = true;

            reload = ReloadFlows;

            prev_id = 0;
            this_id = 0;
            prev_row = null;
            this_row = null;
        }

        private void ReloadFlows(DataTable dt)
        {                        
            gridControl1.DataSource = dt;

            gridView1.PopulateColumns();
            gridView1.Columns[0].Visible = false;

            //gridControl1.RefreshDataSource();
        }

        private void OnTimedEvent(Object source, ElapsedEventArgs e)
        {
            bool res;
            MsgFetchFlowRsp rsp;
            DataTable dt;

            res = RpcClient.FetchFlows(out rsp);

            if (res == false)
                return;

            dt = new DataTable();
            dt.Columns.Add("病人id", typeof(UInt64));
            dt.Columns.Add("申请单号", typeof(string));
            dt.Columns.Add("姓名", typeof(string));
            dt.Columns.Add("检查项目", typeof(string));
            dt.Columns.Add("开单医生", typeof(string));

            for (int i = 0; i < rsp.FlowsCount; i++)
            {
                bool first = true;
                UserFlow n = rsp.GetFlows(i);
                DataRow row = dt.NewRow();

                row[0] = n.UserId;
                row[1] = n.ApplyId.ToString();
                row[2] = n.User;
                row[3] = "";
                row[4] = n.Office + ": " + n.Doctor;
                for (int j = 0; j < n.ItemsCount; j++)
                {
                    if (first)
                    {
                        row[3] += n.GetItems(j);
                        first = false;
                    }
                    else
                    {
                        row[3] += " : " + n.GetItems(j);
                    }
                }

                dt.Rows.Add(row);
            }

            if (this.InvokeRequired)
            {
                this.Invoke(this.reload, dt);
            }
            else
            {
                gridControl1.DataSource = dt;

                gridView1.PopulateColumns();
                gridView1.Columns[0].Visible = false;
            }
            
        }

        private void FlowForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        private void gridControl1_DoubleClick(object sender, EventArgs e)
        {
            try
            {
                GridControl grid = sender as GridControl;
                GridView view = (GridView)grid.Views[0];
                Point pt = view.GridControl.PointToClient(Control.MousePosition);

                DoRowDoubleClick(view, pt);
            }
            catch (Exception er)
            {
                MessageBox.Show(er.ToString());
            }
        }

        private void DoRowDoubleClick(GridView view, Point pt)
        {

            GridHitInfo info = view.CalcHitInfo(pt);

            if (info.InRow || info.InRowCell)
            {
                DataTable dt = (DataTable)gridControl1.DataSource;

                if (this_row == dt.Rows[info.RowHandle])
                    return;

                string show;
                string str;
                show = "申请单号: " + dt.Rows[info.RowHandle][1] + "  姓名：" + dt.Rows[info.RowHandle][2];
                str = "单号: " + dt.Rows[info.RowHandle][1] + "\n姓名：" + dt.Rows[info.RowHandle][2];

                OKForm form = new OKForm(str);
                form.ShowDialog();
                if (form.click == false)
                    return;
                textBox1.Text = show;

                prev_row = this_row;
                this_row = dt.Rows[info.RowHandle];
                
                if (prev_row != null)
                    prev_id = (UInt64)prev_row[0];
                this_id = (UInt64)this_row[0];

                //ComWorker.test();
            }

        }
    }
}