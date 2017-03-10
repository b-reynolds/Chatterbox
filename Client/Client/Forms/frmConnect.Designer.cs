namespace Chatterbox
{
    partial class FrmConnect
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmConnect));
            this.LblPort = new System.Windows.Forms.Label();
            this.LblIP = new System.Windows.Forms.Label();
            this.TxtIP = new System.Windows.Forms.TextBox();
            this.BtnConnect = new System.Windows.Forms.Button();
            this.NudPort = new System.Windows.Forms.NumericUpDown();
            this.StsStrip = new System.Windows.Forms.StatusStrip();
            this.StsLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.MnuStrip = new System.Windows.Forms.MenuStrip();
            this.MnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.MnuHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.MnuExit = new System.Windows.Forms.ToolStripMenuItem();
            this.MnuAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.ImgLogo = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.NudPort)).BeginInit();
            this.StsStrip.SuspendLayout();
            this.MnuStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ImgLogo)).BeginInit();
            this.SuspendLayout();
            // 
            // LblPort
            // 
            this.LblPort.AutoSize = true;
            this.LblPort.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LblPort.Location = new System.Drawing.Point(195, 96);
            this.LblPort.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.LblPort.Name = "LblPort";
            this.LblPort.Size = new System.Drawing.Size(47, 13);
            this.LblPort.TabIndex = 0;
            this.LblPort.Text = "Port:";
            // 
            // LblIP
            // 
            this.LblIP.AutoSize = true;
            this.LblIP.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LblIP.Location = new System.Drawing.Point(32, 96);
            this.LblIP.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.LblIP.Name = "LblIP";
            this.LblIP.Size = new System.Drawing.Size(31, 13);
            this.LblIP.TabIndex = 1;
            this.LblIP.Text = "IP:";
            // 
            // TxtIP
            // 
            this.TxtIP.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtIP.Location = new System.Drawing.Point(67, 93);
            this.TxtIP.Margin = new System.Windows.Forms.Padding(2);
            this.TxtIP.Name = "TxtIP";
            this.TxtIP.Size = new System.Drawing.Size(124, 20);
            this.TxtIP.TabIndex = 1;
            // 
            // BtnConnect
            // 
            this.BtnConnect.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnConnect.Location = new System.Drawing.Point(17, 123);
            this.BtnConnect.Margin = new System.Windows.Forms.Padding(2);
            this.BtnConnect.Name = "BtnConnect";
            this.BtnConnect.Size = new System.Drawing.Size(380, 32);
            this.BtnConnect.TabIndex = 0;
            this.BtnConnect.Text = "Connect";
            this.BtnConnect.UseVisualStyleBackColor = true;
            this.BtnConnect.Click += new System.EventHandler(this.BtnConnect_Click);
            // 
            // NudPort
            // 
            this.NudPort.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NudPort.Location = new System.Drawing.Point(246, 93);
            this.NudPort.Margin = new System.Windows.Forms.Padding(2);
            this.NudPort.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.NudPort.Name = "NudPort";
            this.NudPort.Size = new System.Drawing.Size(133, 20);
            this.NudPort.TabIndex = 2;
            // 
            // StsStrip
            // 
            this.StsStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.StsLabel});
            this.StsStrip.Location = new System.Drawing.Point(0, 169);
            this.StsStrip.Name = "StsStrip";
            this.StsStrip.Size = new System.Drawing.Size(415, 22);
            this.StsStrip.TabIndex = 6;
            // 
            // StsLabel
            // 
            this.StsLabel.BackColor = System.Drawing.SystemColors.Control;
            this.StsLabel.Name = "StsLabel";
            this.StsLabel.Size = new System.Drawing.Size(57, 17);
            this.StsLabel.Text = "Waiting...";
            // 
            // MnuStrip
            // 
            this.MnuStrip.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MnuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MnuFile,
            this.MnuHelp});
            this.MnuStrip.Location = new System.Drawing.Point(0, 0);
            this.MnuStrip.Name = "MnuStrip";
            this.MnuStrip.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.MnuStrip.Size = new System.Drawing.Size(415, 24);
            this.MnuStrip.TabIndex = 7;
            // 
            // MnuFile
            // 
            this.MnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MnuExit});
            this.MnuFile.Name = "MnuFile";
            this.MnuFile.Size = new System.Drawing.Size(47, 20);
            this.MnuFile.Text = "File";
            // 
            // MnuHelp
            // 
            this.MnuHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MnuAbout});
            this.MnuHelp.Name = "MnuHelp";
            this.MnuHelp.Size = new System.Drawing.Size(47, 20);
            this.MnuHelp.Text = "Help";
            // 
            // MnuExit
            // 
            this.MnuExit.Image = global::Chatterbox.Properties.Resources.close;
            this.MnuExit.Name = "MnuExit";
            this.MnuExit.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.MnuExit.Size = new System.Drawing.Size(151, 22);
            this.MnuExit.Text = "Exit";
            this.MnuExit.Click += new System.EventHandler(this.MnuExit_Click);
            // 
            // MnuAbout
            // 
            this.MnuAbout.Image = global::Chatterbox.Properties.Resources.about;
            this.MnuAbout.Name = "MnuAbout";
            this.MnuAbout.Size = new System.Drawing.Size(109, 22);
            this.MnuAbout.Text = "About";
            this.MnuAbout.Click += new System.EventHandler(this.MnuAbout_Click);
            // 
            // ImgLogo
            // 
            this.ImgLogo.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ImgLogo.Image = ((System.Drawing.Image)(resources.GetObject("ImgLogo.Image")));
            this.ImgLogo.Location = new System.Drawing.Point(17, 36);
            this.ImgLogo.Name = "ImgLogo";
            this.ImgLogo.Size = new System.Drawing.Size(380, 48);
            this.ImgLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.ImgLogo.TabIndex = 5;
            this.ImgLogo.TabStop = false;
            // 
            // FrmConnect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ClientSize = new System.Drawing.Size(415, 191);
            this.Controls.Add(this.StsStrip);
            this.Controls.Add(this.MnuStrip);
            this.Controls.Add(this.LblPort);
            this.Controls.Add(this.NudPort);
            this.Controls.Add(this.BtnConnect);
            this.Controls.Add(this.LblIP);
            this.Controls.Add(this.TxtIP);
            this.Controls.Add(this.ImgLogo);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.MnuStrip;
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmConnect";
            this.Text = "Chatterbox";
            this.Load += new System.EventHandler(this.FrmConnect_Load);
            ((System.ComponentModel.ISupportInitialize)(this.NudPort)).EndInit();
            this.StsStrip.ResumeLayout(false);
            this.StsStrip.PerformLayout();
            this.MnuStrip.ResumeLayout(false);
            this.MnuStrip.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ImgLogo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label LblPort;
        private System.Windows.Forms.Label LblIP;
        private System.Windows.Forms.TextBox TxtIP;
        private System.Windows.Forms.Button BtnConnect;
        private System.Windows.Forms.NumericUpDown NudPort;
        private System.Windows.Forms.PictureBox ImgLogo;
        private System.Windows.Forms.StatusStrip StsStrip;
        private System.Windows.Forms.ToolStripStatusLabel StsLabel;
        private System.Windows.Forms.MenuStrip MnuStrip;
        private System.Windows.Forms.ToolStripMenuItem MnuFile;
        private System.Windows.Forms.ToolStripMenuItem MnuExit;
        private System.Windows.Forms.ToolStripMenuItem MnuHelp;
        private System.Windows.Forms.ToolStripMenuItem MnuAbout;
    }
}