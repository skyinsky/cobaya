namespace cobaya
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
            this.修改密码 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.亲属通道ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.紧急通道ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.contextMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // notifyIcon
            // 
            this.notifyIcon.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.notifyIcon.ContextMenuStrip = this.contextMenuStrip;
            this.notifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon.Icon")));
            this.notifyIcon.Visible = true;
            this.notifyIcon.MouseClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon_MouseClick);
            this.notifyIcon.MouseMove += new System.Windows.Forms.MouseEventHandler(this.notifyIcon_MouseMove);
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.登录服务,
            this.注销服务,
            this.toolStripSeparator1,
            this.修改密码,
            this.toolStripSeparator3,
            this.亲属通道ToolStripMenuItem,
            this.紧急通道ToolStripMenuItem});
            this.contextMenuStrip.Name = "contextMenuStrip";
            this.contextMenuStrip.Size = new System.Drawing.Size(153, 148);
            // 
            // 登录服务
            // 
            this.登录服务.Image = ((System.Drawing.Image)(resources.GetObject("登录服务.Image")));
            this.登录服务.Name = "登录服务";
            this.登录服务.Size = new System.Drawing.Size(152, 22);
            this.登录服务.Text = "登录服务";
            this.登录服务.ToolTipText = "无聊的一天又开始了，真辛苦o(∩_∩)o ";
            this.登录服务.Click += new System.EventHandler(this.登录服务_Click);
            // 
            // 注销服务
            // 
            this.注销服务.Image = ((System.Drawing.Image)(resources.GetObject("注销服务.Image")));
            this.注销服务.Name = "注销服务";
            this.注销服务.Size = new System.Drawing.Size(152, 22);
            this.注销服务.Text = "注销服务";
            this.注销服务.ToolTipText = "好不容易熬到现在，点下我吧o(∩_∩)o ";
            this.注销服务.Click += new System.EventHandler(this.注销服务_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(149, 6);
            // 
            // 修改密码
            // 
            this.修改密码.Image = ((System.Drawing.Image)(resources.GetObject("修改密码.Image")));
            this.修改密码.Name = "修改密码";
            this.修改密码.Size = new System.Drawing.Size(152, 22);
            this.修改密码.Text = "修改密码";
            this.修改密码.ToolTipText = "初始密码111111，要不要改改呢:-)";
            this.修改密码.Click += new System.EventHandler(this.修改密码_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(149, 6);
            // 
            // 亲属通道ToolStripMenuItem
            // 
            this.亲属通道ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("亲属通道ToolStripMenuItem.Image")));
            this.亲属通道ToolStripMenuItem.Name = "亲属通道ToolStripMenuItem";
            this.亲属通道ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.亲属通道ToolStripMenuItem.Text = "家属通道";
            this.亲属通道ToolStripMenuItem.ToolTipText = "听说家属有优惠，不信你试试o(∩_∩)o ";
            this.亲属通道ToolStripMenuItem.Click += new System.EventHandler(this.亲属通道ToolStripMenuItem_Click);
            // 
            // 紧急通道ToolStripMenuItem
            // 
            this.紧急通道ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("紧急通道ToolStripMenuItem.Image")));
            this.紧急通道ToolStripMenuItem.Name = "紧急通道ToolStripMenuItem";
            this.紧急通道ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.紧急通道ToolStripMenuItem.Text = "紧急通道";
            this.紧急通道ToolStripMenuItem.ToolTipText = "没缴费的紧急事件走这里！";
            this.紧急通道ToolStripMenuItem.Click += new System.EventHandler(this.紧急通道ToolStripMenuItem_Click);
            // 
            // labelControl1
            // 
            this.labelControl1.Appearance.Font = new System.Drawing.Font("隶书", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelControl1.Appearance.ForeColor = System.Drawing.Color.Cyan;
            this.labelControl1.Location = new System.Drawing.Point(200, 227);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(242, 16);
            this.labelControl1.TabIndex = 1;
            this.labelControl1.Text = "香河县人民医院医疗设备监控服务";
            // 
            // timer2
            // 
            this.timer2.Enabled = true;
            this.timer2.Interval = 3000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // MainFrame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayoutStore = System.Windows.Forms.ImageLayout.Zoom;
            this.BackgroundImageStore = global::cobaya.Properties.Resources.香河人民医院;
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
            this.TopMost = true;
            this.contextMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NotifyIcon notifyIcon;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem 登录服务;
        private System.Windows.Forms.ToolStripMenuItem 注销服务;
        private System.Windows.Forms.ToolStripMenuItem 修改密码;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem 亲属通道ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 紧急通道ToolStripMenuItem;
    }
}