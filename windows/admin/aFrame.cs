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
    public partial class aMainFrame : RibbonForm
    {
        public aMainFrame()
        {
            InitializeComponent();           
            InitSkinGallery();
        }

        void InitSkinGallery()
        {
            SkinHelper.InitSkinGallery(rgbiSkins, true);
        }

        public bool InitTreeList()
        {
            //foreach (DataRow room in Info.tlb_dev.Rows)
            //{
            //    string keshi_num = room["科室编号"].ToString();
            //    string keshi_name = room["科室名称"].ToString();

            //    //科室列表
            //    TreeNode keshi_ = new TreeNode(keshi_name);
            //    //加入科室列表
            //    this.devs.Nodes.Add(keshi_);

            //    //设备列表
            //    DataRow[] devs = Info.tlb_dev.Select("科室编号=" + keshi_num);
            //    TreeNode[] dev_nodes = new TreeNode[devs.Length];
            //    for (int i = 0; i < devs.Length; i++)
            //    {
            //        dev_nodes[i] = new TreeNode();
            //        dev_nodes[i].Name = devs[i]["名称"].ToString();
            //        dev_nodes[i].Text = devs[i]["名称"].ToString();
            //        dev_nodes[i].ImageIndex = 2;
            //        dev_nodes[i].SelectedImageIndex = 2;
            //    }
            //    TreeNode keshi_dev = new TreeNode("", dev_nodes);
            //    keshi_dev.Name = keshi_name;
            //    keshi_dev.Text = keshi_name;

            //    //加入设备列表
            //    this.users.Nodes.Add(keshi_dev);

            //}

            try
            {

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

        private void devs_AfterExpand(object sender, TreeViewEventArgs e)
        {
            e.Node.ImageIndex = 1;
        }

        private void devs_AfterCollapse(object sender, TreeViewEventArgs e)
        {
            e.Node.ImageIndex = 0;
        }

        private void devs_MouseClick(object sender, MouseEventArgs e)
        {
            TreeNode node = this.users.GetNodeAt(new Point(e.X, e.Y));
            if (node == null)
                return;

            if (this.devs.SelectedNode != null && this.devs.SelectedNode.IsSelected)
            {
                this.devs.SelectedNode.SelectedImageIndex = 4;
            }
            //if (this.dots.SelectedNode != null && this.dots.SelectedNode.IsSelected)
            //{
            //    if (this.dots.SelectedNode.Parent == null)
            //    {
            //        if (this.dots.SelectedNode.IsExpanded)
            //            this.dots.SelectedNode.SelectedImageIndex = 1;
            //        else
            //            this.dots.SelectedNode.SelectedImageIndex = 0;
            //    }
            //    else
            //    {
            //        this.dots.SelectedNode.SelectedImageIndex = 3;
            //    }
            //}

            node.SelectedImageIndex = 5;
        }

        private void dots_AfterCollapse(object sender, TreeViewEventArgs e)
        {
            e.Node.ImageIndex = 1;
        }

        private void dots_AfterExpand(object sender, TreeViewEventArgs e)
        {
            e.Node.ImageIndex = 0;
        }


        private void dots_MouseClick(object sender, MouseEventArgs e)
        {
            //TreeNode node = this.dots.GetNodeAt(new Point(e.X, e.Y));
            //if (node == null)
            //    return;

            //if (this.devs.SelectedNode != null && this.devs.SelectedNode.IsSelected)
            //{
            //    this.devs.SelectedNode.SelectedImageIndex = 4;
            //}
            //if (this.users.SelectedNode != null && this.users.SelectedNode.IsSelected)
            //{
            //    if (this.users.SelectedNode.Parent == null)
            //    {
            //        if (this.users.SelectedNode.IsExpanded)
            //            this.users.SelectedNode.SelectedImageIndex = 1;
            //        else
            //            this.users.SelectedNode.SelectedImageIndex = 0;
            //    }
            //    else
            //    {
            //        this.users.SelectedNode.SelectedImageIndex = 2;
            //    }
            //}

            //node.SelectedImageIndex = 5;
        }

        //private void devs_MouseClick(object sender, MouseEventArgs e)
        //{
            //TreeNode node = this.devs.GetNodeAt(new Point(e.X, e.Y));
            //if (node == null)
            //    return;

            //if (this.users.SelectedNode != null && this.users.SelectedNode.IsSelected)
            //{
            //    if (this.users.SelectedNode.Parent == null)
            //    {
            //        if (this.users.SelectedNode.IsExpanded)
            //            this.users.SelectedNode.SelectedImageIndex = 1;
            //        else
            //            this.users.SelectedNode.SelectedImageIndex = 0;
            //    }
            //    else
            //    {
            //        this.users.SelectedNode.SelectedImageIndex = 2;
            //    }
            //}
            //if (this.dots.SelectedNode != null && this.dots.SelectedNode.IsSelected)
            //{
            //    if (this.dots.SelectedNode.Parent == null)
            //    {
            //        if (this.dots.SelectedNode.IsExpanded)
            //            this.dots.SelectedNode.SelectedImageIndex = 1;
            //        else
            //            this.dots.SelectedNode.SelectedImageIndex = 0;
            //    }
            //    else
            //    {
            //        this.dots.SelectedNode.SelectedImageIndex = 3;
            //    }
            //}

            //node.SelectedImageIndex = 5;
        //}

        private string get_room_num(object sender, MouseEventArgs e)
        {
            //TreeNode node = this.devs.GetNodeAt(new Point(e.X, e.Y));
            //if (node == null)
            //    return null;

            //foreach (DataRow room in Info.tlb_office.Rows)
            //{
            //    if (room["科室名称"] == node.Text)
            //        return room["科室编号"].ToString();
            //}
            //return null;
            return null;
        }

        private void devs_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            DataTable dt = null;

            // |设备编号| 设备名称| 医生姓名| 时间| 备注|

            string room_num = get_room_num(sender, e);
            if (room_num == null)
                return;

            string time_begin = "'" + this.dateTimeBegin.Value.ToString() + "'";
            string time_end = "'" + this.dateTimeEnd.Value.ToString() + "'";
            string sql = "SELECT `违规`.`设备编号`, `违规`.`设备名称`, `违规`.`医生姓名`, `违规`.`时间`, `违规`.`备注` FROM `违规` WHERE `违规`.`时间` >=  "
                + time_begin + " AND `违规`.`时间` <=" + time_end + " AND `违规`.`科室编号` =  '" + room_num + "' ORDER BY `违规`.`设备编号` ASC";

            try
            {
                dt = libMySQL.db_query(sql);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }

            this.gridControl1.DataSource = dt;
            this.gridView1.PopulateColumns();
            this.gridView1.Columns["时间"].DisplayFormat.FormatType = FormatType.DateTime;
            this.gridView1.Columns["时间"].DisplayFormat.FormatString = "yyyy-mm-dd hh:mm:ss";
        }

        private string get_dev_num(object sender, MouseEventArgs e)
        {
            TreeNode node = this.users.GetNodeAt(new Point(e.X, e.Y));
            if (node == null)
                return null;
            if (node.Parent == null)
                return null;

            foreach (DataRow dev in Info.tlb_dev.Rows)
            {
                if (dev["名称"] == node.Text)
                    return dev["设备编号"].ToString();
            }
            return null;
        }

        //private void devs_MouseDoubleClick(object sender, MouseEventArgs e)
        //{
        //    DataTable dt = null;

        //    string dev_num = get_dev_num(sender, e);
        //    if (dev_num == null)
        //        return;

        //    // |科室名称| 医生姓名| 时间| 备注|

        //    //setting.dlg_login.splashScreenManager1.ShowWaitForm();

        //    string time_begin = "'" + this.dateTimeBegin.Value.ToString() + "'";
        //    string time_end = "'" + this.dateTimeEnd.Value.ToString() + "'";
        //    string sql = "SELECT `违规`.`科室名称`, `违规`.`医生姓名`, `违规`.`时间`, `违规`.`备注` FROM `违规` WHERE `违规`.`时间` >=  "
        //        + time_begin + " AND `违规`.`时间` <=" + time_end + " AND `违规`.`设备编号` =  '" + dev_num + "' ORDER BY `违规`.`科室编号` ASC";
            
        //    try
        //    {
        //        dt = libMySQL.db_query(Info.mysql_con, sql);
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.Message);
        //        return;
        //    }

        //    this.gridControl1.DataSource = dt;
        //    this.gridView1.PopulateColumns();
        //    this.gridView1.Columns["时间"].DisplayFormat.FormatType = FormatType.DateTime;
        //    this.gridView1.Columns["时间"].DisplayFormat.FormatString = "yyyy-mm-dd hh:mm:ss";

        //    //setting.dlg_login.splashScreenManager1.CloseWaitForm();
        //}

        //private string get_dot_num(object sender, MouseEventArgs e)
        //{
        //    //TreeNode node = this.dots.GetNodeAt(new Point(e.X, e.Y));
        //    //if (node == null)
        //    //    return null;
        //    //if (node.Parent == null)
        //    //    return null;

        //    //foreach (DataRow dot in Info.tlb_user.Rows)
        //    //{
        //    //    if (dot["姓名"] == node.Text)
        //    //        return dot["医生编号"].ToString();
        //    //}
        //    return null;
        //}

        //private void dots_MouseDoubleClick(object sender, MouseEventArgs e)
        //{
        //    DataTable dt = null;

        //    string dot_num = get_dot_num(sender, e);
        //    if (dot_num == null)
        //        return;

        //    // |科室名称| 设备编号| 设备名称| 时间| 备注|

        //    //setting.dlg_login.splashScreenManager1.ShowWaitForm();

        //    string time_begin = "'" + this.dateTimeBegin.Value.ToString() + "'";
        //    string time_end = "'" + this.dateTimeEnd.Value.ToString() + "'";
        //    string sql = "SELECT `违规`.`科室名称`, `违规`.`设备编号`, `违规`.`设备名称`, `违规`.`时间`, `违规`.`备注` FROM `违规` WHERE `违规`.`时间` >=  "
        //        + time_begin + " AND `违规`.`时间` <=" + time_end + " AND `违规`.`医生编号` =  '" + dot_num + "' ORDER BY `违规`.`科室编号` ASC";

        //    try
        //    {
        //        dt = libMySQL.db_query(Info.mysql_con, sql);
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.Message);
        //        return;
        //    }

        //    this.gridControl1.DataSource = dt;
        //    this.gridView1.PopulateColumns();
        //    this.gridView1.Columns["时间"].DisplayFormat.FormatType = FormatType.DateTime;
        //    this.gridView1.Columns["时间"].DisplayFormat.FormatString = "yyyy-mm-dd hh:mm:ss";

        //    //setting.dlg_login.splashScreenManager1.CloseWaitForm();
        //}
    }
}