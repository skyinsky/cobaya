namespace cobaya
{
    partial class UpdateForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UpdateForm));
            this.oklogin = new System.Windows.Forms.Button();
            this.cancel = new System.Windows.Forms.Button();
            this.userbox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.passbox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.newPasswd1 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.newPasswd2 = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // oklogin
            // 
            resources.ApplyResources(this.oklogin, "oklogin");
            this.oklogin.Name = "oklogin";
            this.oklogin.UseVisualStyleBackColor = true;
            this.oklogin.Click += new System.EventHandler(this.oklogin_Click);
            // 
            // cancel
            // 
            this.cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            resources.ApplyResources(this.cancel, "cancel");
            this.cancel.Name = "cancel";
            this.cancel.UseVisualStyleBackColor = true;
            this.cancel.Click += new System.EventHandler(this.cancel_Click);
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
            // passbox
            // 
            resources.ApplyResources(this.passbox, "passbox");
            this.passbox.Name = "passbox";
            this.passbox.UseSystemPasswordChar = true;
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // label3
            // 
            resources.ApplyResources(this.label3, "label3");
            this.label3.Name = "label3";
            // 
            // newPasswd1
            // 
            resources.ApplyResources(this.newPasswd1, "newPasswd1");
            this.newPasswd1.Name = "newPasswd1";
            this.newPasswd1.UseSystemPasswordChar = true;
            // 
            // label4
            // 
            resources.ApplyResources(this.label4, "label4");
            this.label4.Name = "label4";
            // 
            // newPasswd2
            // 
            resources.ApplyResources(this.newPasswd2, "newPasswd2");
            this.newPasswd2.Name = "newPasswd2";
            this.newPasswd2.UseSystemPasswordChar = true;
            // 
            // UpdateForm
            // 
            this.AcceptButton = this.oklogin;
            this.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancel;
            this.ControlBox = false;
            this.Controls.Add(this.label4);
            this.Controls.Add(this.newPasswd2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.newPasswd1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.passbox);
            this.Controls.Add(this.userbox);
            this.Controls.Add(this.cancel);
            this.Controls.Add(this.oklogin);
            this.FormBorderEffect = DevExpress.XtraEditors.FormBorderEffect.Shadow;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "UpdateForm";
            this.ShowInTaskbar = false;
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button oklogin;
        private System.Windows.Forms.Button cancel;
        private System.Windows.Forms.TextBox userbox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox passbox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox newPasswd1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox newPasswd2;

    }
}