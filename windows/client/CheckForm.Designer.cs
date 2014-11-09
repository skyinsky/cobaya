﻿namespace cobaya
{
    partial class CheckForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CheckForm));
            this.oklogin = new System.Windows.Forms.Button();
            this.userbox = new System.Windows.Forms.TextBox();
            this.splashScreenManager1 = new DevExpress.XtraSplashScreen.SplashScreenManager(this, typeof(global::cobaya.RWaitForm), true, true);
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.check_show = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // oklogin
            // 
            resources.ApplyResources(this.oklogin, "oklogin");
            this.oklogin.Name = "oklogin";
            this.oklogin.UseVisualStyleBackColor = true;
            this.oklogin.Click += new System.EventHandler(this.ok_click);
            // 
            // userbox
            // 
            resources.ApplyResources(this.userbox, "userbox");
            this.userbox.Name = "userbox";
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // button1
            // 
            resources.ApplyResources(this.button1, "button1");
            this.button1.Name = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.clear_Click);
            // 
            // check_show
            // 
            resources.ApplyResources(this.check_show, "check_show");
            this.check_show.ForeColor = System.Drawing.Color.OrangeRed;
            this.check_show.Name = "check_show";
            // 
            // CheckForm
            // 
            this.AcceptButton = this.oklogin;
            this.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ControlBox = false;
            this.Controls.Add(this.check_show);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.userbox);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.oklogin);
            this.FormBorderEffect = DevExpress.XtraEditors.FormBorderEffect.Shadow;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "CheckForm";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.CheckForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button oklogin;
        private System.Windows.Forms.TextBox userbox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label check_show;
        private DevExpress.XtraSplashScreen.SplashScreenManager splashScreenManager1;

    }
}