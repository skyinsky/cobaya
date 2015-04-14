using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.Skins;
using DevExpress.LookAndFeel;
using DevExpress.UserSkins;
using DevExpress.XtraBars;
using DevExpress.XtraBars.Ribbon;
using DevExpress.XtraBars.Helpers;
using DevExpress.Utils;

namespace cobaya
{
    public partial class MainFrame : RibbonForm
    {
        public MainFrame()
        {
            InitializeComponent();           
            InitSkinGallery();

            this.dateTimeEnd.Value = DateTime.Now;
            this.dateTimeBegin.Value = DateTime.Now.AddDays(-30);
        }

        void InitSkinGallery()
        {
            SkinHelper.InitSkinGallery(rgbiSkins, true);
        }

        public bool InitTreeList()
        {
            try
            {
                //院区
                Queue<string> areas = new Queue<string>();
                foreach (DataRow row in Info.tlb_dev.Rows)
                {
                    bool hit = false;

                    foreach (string area in areas)
                    {
                        if (area == row["院区"].ToString())
                        {
                            hit = true;
                            break;
                        }
                    }

                    if (!hit)
                        areas.Enqueue(row["院区"].ToString());
                }

                //每一个院区
                foreach (string area in areas)
                {
                    List<DataRow> mix = new List<DataRow>();
                    foreach (DataRow row in Info.tlb_dev.Rows)
                    {
                        if (row["院区"].ToString() == area)
                            mix.Add(row);
                    }

                    //科室
                    List<string> offices = new List<string>();
                    foreach (DataRow row in mix)
                    {
                        bool hit = false;

                        foreach (string office in offices)
                        {
                            if (office == row["科室名称"].ToString())
                            {
                                hit = true;
                                break;
                            }
                        }

                        if (!hit)
                            offices.Add(row["科室名称"].ToString());
                    }

                    //科室节点
                    TreeNode[] office_nodes = new TreeNode[offices.Count];

                    //每一个科室                    
                    for (int i = 0; i < office_nodes.Length; i++)
                    {
                        string office = offices[i];
                        List<string> _devs = new List<string>();

                        //设备
                        foreach (DataRow row in mix)
                        {
                            if (office != row["科室名称"].ToString())
                                continue;

                            _devs.Add(row["器械名称"].ToString());
                        }

                        TreeNode[] dev_nodes = new TreeNode[_devs.Count];
                        for (int j = 0; j < dev_nodes.Length; j++)
                        {
                            string txt = _devs[j];

                            TreeNode node = new TreeNode();
                            node.Name = txt;
                            node.Text = txt;
                            node.ImageIndex = 2;
                            node.SelectedImageIndex = 2;

                            dev_nodes[j] = node;
                        }

                        office_nodes[i] = new TreeNode("", dev_nodes);
                        office_nodes[i].Name = office;
                        office_nodes[i].Text = office;
                        office_nodes[i].ImageIndex = 1;
                        office_nodes[i].SelectedImageIndex = 1;
                    }

                    TreeNode area_node = new TreeNode("", office_nodes);
                    area_node.Name = area;
                    area_node.Text = area;
                    area_node.ImageIndex = 0;
                    area_node.SelectedImageIndex = 0;

                    this.devs.Nodes.Add(area_node);
                }

                //医生列表
                foreach (DataRow row in Info.tlb_user.Rows)
                {
                    TreeNode node = new TreeNode();
                    node.Name = row["姓名"].ToString();
                    node.Text = row["姓名"].ToString();
                    node.ImageIndex = 3;
                    node.SelectedImageIndex = 3;

                    this.users.Nodes.Add(node);
                }

                return true;
            }
            catch (Exception e)
            {
                string err = "请联系管理员\n" + e.ToString();

                MessageBox.Show(err);

                return false;
            }
        }

        private void ClearTreeList()
        {
            this.users.Nodes.Clear();
            this.devs.Nodes.Clear();
        }

        private string get_office(object sender, MouseEventArgs e)
        {
            TreeNode node = this.devs.GetNodeAt(new Point(e.X, e.Y));
            if (node == null)
                return null;

            if (node.Parent == null || node.Parent.Parent == null)
                return null;

            return node.Parent.Name;
        }

        private string get_area(object sender, MouseEventArgs e)
        {
            TreeNode node = this.devs.GetNodeAt(new Point(e.X, e.Y));
            if (node == null)
                return null;

            if (node.Parent == null || node.Parent.Parent == null)
                return null;

            return node.Parent.Parent.Name;
        }

        private void devs_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            string office = get_office(sender, e);
            if (office == null)
                return;

            string area = get_area(sender, e);
            if (area == null)
                return;

            DataTable dt = null;

            splashScreenManager1.ShowWaitForm();

            string time_begin = "'" + this.dateTimeBegin.Value.ToString() + "'";
            string time_end = "'" + this.dateTimeEnd.Value.ToString() + "'";
            string sql = "SELECT `日志`.`操作员`, `日志`.`登录终端`, `日志`.`时间` FROM `日志` WHERE "
                + " `日志`.`时间` >= " + time_begin + " AND `日志`.`时间` <= " + time_end 
                + " AND `日志`.`科室名称` = '" + office + "' AND `日志`.`院区` = '" + area
                + "' ORDER BY `日志`.`时间` ASC";

            try
            {
                dt = libMySQL.db_query(sql);
            }
            catch (Exception ex)
            {
                splashScreenManager1.CloseWaitForm();
                MessageBox.Show(ex.Message);
                return;
            }

            this.gridControl1.DataSource = dt;
            this.gridView1.PopulateColumns();
            this.gridView1.Columns["时间"].DisplayFormat.FormatType = FormatType.DateTime;
            this.gridView1.Columns["时间"].DisplayFormat.FormatString = "yyyy-MM-dd hh:mm:ss";
            splashScreenManager1.CloseWaitForm();
        }

        private string get_user(object sender, MouseEventArgs e)
        {
            TreeNode node = this.users.GetNodeAt(new Point(e.X, e.Y));
            if (node == null)
                return null;

            return node.Name;
        }


        private void users_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            string user = get_user(sender, e);
            if (user == null)
                return;

            DataTable dt = null;

            splashScreenManager1.ShowWaitForm();

            string time_begin = "'" + this.dateTimeBegin.Value.ToString() + "'";
            string time_end = "'" + this.dateTimeEnd.Value.ToString() + "'";
            string sql = "SELECT `日志`.`登录终端`,`日志`.`时间`," 
                + "`日志`.`器械名称`,`日志`.`科室名称`,`日志`.`院区`"
                + " FROM `日志` WHERE "
                + " `日志`.`时间` >= " + time_begin + " AND `日志`.`时间` <= " + time_end 
                + " AND `日志`.`操作员` = '" + user
                + "' ORDER BY `日志`.`时间` ASC";

            try
            {

                dt = libMySQL.db_query(sql);
            }
            catch (Exception ex)
            {
                splashScreenManager1.CloseWaitForm();
                MessageBox.Show(ex.Message);
                return;
            }

            this.gridControl1.DataSource = dt;
            this.gridView1.PopulateColumns();
            this.gridView1.Columns["时间"].DisplayFormat.FormatType = FormatType.DateTime;
            this.gridView1.Columns["时间"].DisplayFormat.FormatString = "yyyy-MM-dd hh:mm:ss";
            splashScreenManager1.CloseWaitForm();
        
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            DataTable dt = null;

            splashScreenManager1.ShowWaitForm();

            string time_begin = "'" + this.dateTimeBegin.Value.ToString() + "'";
            string time_end = "'" + this.dateTimeEnd.Value.ToString() + "'";
            string sql = "SELECT `异常`.`异常时间`, `异常`.`器械名称`, `异常`.`科室名称`, `异常`.`院区` "
                + "FROM `异常` WHERE `异常`.`异常时间` >= " +  time_begin 
                +" AND `异常`.`异常时间` <= " + time_end
                + " ORDER BY `异常`.`异常时间` ASC";

            try
            {

                dt = libMySQL.db_query(sql);
            }
            catch (Exception ex)
            {
                splashScreenManager1.CloseWaitForm();
                MessageBox.Show(ex.Message);
                return;
            }

            this.gridControl1.DataSource = dt;
            this.gridView1.PopulateColumns();
            this.gridView1.Columns["异常时间"].DisplayFormat.FormatType = FormatType.DateTime;
            this.gridView1.Columns["异常时间"].DisplayFormat.FormatString = "yyyy-MM-dd hh:mm:ss";
            splashScreenManager1.CloseWaitForm();
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            UserForm form = new UserForm();

            form.ShowDialog();

            if (!form.res)
                return;

            splashScreenManager1.ShowWaitForm();
            if (!Info.LoadDatabase())
            {
                splashScreenManager1.CloseWaitForm();
                return;
            }
            ClearTreeList();
            if (!InitTreeList())
            {
                splashScreenManager1.CloseWaitForm();
                return;
            }
            splashScreenManager1.CloseWaitForm();
        }

        private void 家属通道_Click(object sender, EventArgs e)
        {
            DataTable dt = null;

            splashScreenManager1.ShowWaitForm();

            string time_begin = "'" + this.dateTimeBegin.Value.ToString() + "'";
            string time_end = "'" + this.dateTimeEnd.Value.ToString() + "'";

            string sql = "SELECT `亲属`.`时间`,`亲属`.`操作医生`,`亲属`.`器械名称`, `亲属`.`科室名称`, `亲属`.`院区`, `亲属`.`备注` "
                + "FROM `亲属` WHERE `亲属`.`时间` >= " + time_begin
                + " AND `亲属`.`时间` <= " + time_end
                + " ORDER BY `亲属`.`时间` ASC";

            try
            {

                dt = libMySQL.db_query(sql);
            }
            catch (Exception ex)
            {
                splashScreenManager1.CloseWaitForm();
                MessageBox.Show(ex.Message);
                return;
            }

            this.gridControl1.DataSource = dt;
            this.gridView1.PopulateColumns();
            this.gridView1.Columns["时间"].DisplayFormat.FormatType = FormatType.DateTime;
            this.gridView1.Columns["时间"].DisplayFormat.FormatString = "yyyy-MM-dd hh:mm:ss";
            splashScreenManager1.CloseWaitForm();
        }

        private void 紧急通道_Click(object sender, EventArgs e)
        {
            DataTable dt = null;

            splashScreenManager1.ShowWaitForm();

            string time_begin = "'" + this.dateTimeBegin.Value.ToString() + "'";
            string time_end = "'" + this.dateTimeEnd.Value.ToString() + "'";

            string sql = "SELECT `紧急`.`时间`,`紧急`.`操作医生`,`紧急`.`器械名称`, `紧急`.`科室名称`, `紧急`.`院区`, `紧急`.`备注` "
                + "FROM `紧急` WHERE `紧急`.`时间` >= " + time_begin
                + " AND `紧急`.`时间` <= " + time_end
                + " ORDER BY `紧急`.`时间` ASC";

            try
            {

                dt = libMySQL.db_query(sql);
            }
            catch (Exception ex)
            {
                splashScreenManager1.CloseWaitForm();
                MessageBox.Show(ex.Message);
                return;
            }

            this.gridControl1.DataSource = dt;
            this.gridView1.PopulateColumns();
            this.gridView1.Columns["时间"].DisplayFormat.FormatType = FormatType.DateTime;
            this.gridView1.Columns["时间"].DisplayFormat.FormatString = "yyyy-MM-dd hh:mm:ss";
            splashScreenManager1.CloseWaitForm();
        }
    }
}