namespace MedTool
{
    partial class MainFrame
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainFrame));
            this.notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.登录服务 = new System.Windows.Forms.ToolStripMenuItem();
            this.注销服务 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.查询记录 = new System.Windows.Forms.ToolStripMenuItem();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.contextMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // notifyIcon
            // 
            this.notifyIcon.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.notifyIcon.BalloonTipText = "香河县人民医院医疗设备监控服务";
            this.notifyIcon.ContextMenuStrip = this.contextMenuStrip;
            this.notifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon.Icon")));
            this.notifyIcon.Text = "香河县人民医院医疗设备监控服务";
            this.notifyIcon.Visible = true;
            this.notifyIcon.MouseClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon_MouseClick);
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.登录服务,
            this.注销服务,
            this.toolStripSeparator1,
            this.查询记录});
            this.contextMenuStrip.Name = "contextMenuStrip";
            this.contextMenuStrip.Size = new System.Drawing.Size(153, 98);
            // 
            // 登录服务
            // 
            this.登录服务.Image = ((System.Drawing.Image)(resources.GetObject("登录服务.Image")));
            this.登录服务.Name = "登录服务";
            this.登录服务.Size = new System.Drawing.Size(152, 22);
            this.登录服务.Text = "登录服务";
            this.登录服务.ToolTipText = "亲，工作辛苦了！";
            this.登录服务.Click += new System.EventHandler(this.登录服务_Click);
            // 
            // 注销服务
            // 
            this.注销服务.Image = ((System.Drawing.Image)(resources.GetObject("注销服务.Image")));
            this.注销服务.Name = "注销服务";
            this.注销服务.Size = new System.Drawing.Size(152, 22);
            this.注销服务.Text = "注销服务";
            this.注销服务.ToolTipText = "亲，下班了，记得注销哦！";
            this.注销服务.Click += new System.EventHandler(this.注销服务_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(149, 6);
            // 
            // 查询记录
            // 
            this.查询记录.Image = ((System.Drawing.Image)(resources.GetObject("查询记录.Image")));
            this.查询记录.Name = "查询记录";
            this.查询记录.Size = new System.Drawing.Size(152, 22);
            this.查询记录.Text = "查询记录";
            this.查询记录.ToolTipText = "查询历史记录";
            this.查询记录.Click += new System.EventHandler(this.查询记录_Click);
            // 
            // labelControl1
            // 
            this.labelControl1.Appearance.Font = new System.Drawing.Font("隶书", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelControl1.Appearance.ForeColor = System.Drawing.Color.AntiqueWhite;
            this.labelControl1.LineVisible = true;
            this.labelControl1.Location = new System.Drawing.Point(197, 229);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(240, 16);
            this.labelControl1.TabIndex = 1;
            this.labelControl1.Text = "香河县人民医院医疗设备监控服务";
            // 
            // MainFrame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayoutStore = System.Windows.Forms.ImageLayout.Zoom;
            this.BackgroundImageStore = global::MedTool.Properties.Resources.香河人民医院;
            this.ClientSize = new System.Drawing.Size(485, 289);
            this.Controls.Add(this.labelControl1);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainFrame";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "MainFrame";
            this.contextMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NotifyIcon notifyIcon;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem 登录服务;
        private System.Windows.Forms.ToolStripMenuItem 注销服务;
        private System.Windows.Forms.ToolStripMenuItem 查询记录;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private DevExpress.XtraEditors.LabelControl labelControl1;
    }
}