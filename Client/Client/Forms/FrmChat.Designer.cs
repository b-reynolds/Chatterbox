namespace Chatterbox.Forms {
    partial class FrmChat {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmChat));
            this.TxtMessage = new System.Windows.Forms.TextBox();
            this.RTxtFeed = new System.Windows.Forms.RichTextBox();
            this.LstUsers = new System.Windows.Forms.ListBox();
            this.LstRooms = new System.Windows.Forms.ListBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.MnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.MnuExit = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MnuCommands = new System.Windows.Forms.ToolStripMenuItem();
            this.MnuAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.ImgInterface = new System.Windows.Forms.PictureBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ImgInterface)).BeginInit();
            this.SuspendLayout();
            // 
            // TxtMessage
            // 
            this.TxtMessage.BackColor = System.Drawing.Color.White;
            this.TxtMessage.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.TxtMessage.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtMessage.ForeColor = System.Drawing.Color.Black;
            this.TxtMessage.Location = new System.Drawing.Point(26, 335);
            this.TxtMessage.Margin = new System.Windows.Forms.Padding(2);
            this.TxtMessage.MaxLength = 128;
            this.TxtMessage.Name = "TxtMessage";
            this.TxtMessage.Size = new System.Drawing.Size(900, 15);
            this.TxtMessage.TabIndex = 1;
            this.TxtMessage.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TxtMessage_KeyPress);
            // 
            // RTxtFeed
            // 
            this.RTxtFeed.BackColor = System.Drawing.Color.White;
            this.RTxtFeed.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.RTxtFeed.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RTxtFeed.ForeColor = System.Drawing.Color.Black;
            this.RTxtFeed.Location = new System.Drawing.Point(166, 61);
            this.RTxtFeed.Margin = new System.Windows.Forms.Padding(2);
            this.RTxtFeed.Name = "RTxtFeed";
            this.RTxtFeed.ReadOnly = true;
            this.RTxtFeed.Size = new System.Drawing.Size(566, 245);
            this.RTxtFeed.TabIndex = 3;
            this.RTxtFeed.Text = "";
            this.RTxtFeed.TextChanged += new System.EventHandler(this.RTxtFeed_TextChanged);
            // 
            // LstUsers
            // 
            this.LstUsers.BackColor = System.Drawing.Color.White;
            this.LstUsers.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.LstUsers.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LstUsers.ForeColor = System.Drawing.Color.Black;
            this.LstUsers.FormattingEnabled = true;
            this.LstUsers.IntegralHeight = false;
            this.LstUsers.ItemHeight = 14;
            this.LstUsers.Location = new System.Drawing.Point(19, 62);
            this.LstUsers.Margin = new System.Windows.Forms.Padding(2);
            this.LstUsers.Name = "LstUsers";
            this.LstUsers.Size = new System.Drawing.Size(125, 244);
            this.LstUsers.TabIndex = 4;
            this.LstUsers.MouseDown += new System.Windows.Forms.MouseEventHandler(this.LstUsers_MouseDown);
            // 
            // LstRooms
            // 
            this.LstRooms.BackColor = System.Drawing.Color.White;
            this.LstRooms.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.LstRooms.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LstRooms.ForeColor = System.Drawing.Color.Black;
            this.LstRooms.FormattingEnabled = true;
            this.LstRooms.IntegralHeight = false;
            this.LstRooms.ItemHeight = 14;
            this.LstRooms.Location = new System.Drawing.Point(757, 61);
            this.LstRooms.Margin = new System.Windows.Forms.Padding(2);
            this.LstRooms.Name = "LstRooms";
            this.LstRooms.Size = new System.Drawing.Size(181, 245);
            this.LstRooms.TabIndex = 6;
            this.LstRooms.MouseDown += new System.Windows.Forms.MouseEventHandler(this.LstRooms_MouseDown);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MnuFile,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.menuStrip1.Size = new System.Drawing.Size(958, 24);
            this.menuStrip1.TabIndex = 9;
            this.menuStrip1.Text = "MnuStrip";
            // 
            // MnuFile
            // 
            this.MnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MnuExit});
            this.MnuFile.Name = "MnuFile";
            this.MnuFile.Size = new System.Drawing.Size(37, 20);
            this.MnuFile.Text = "File";
            // 
            // MnuExit
            // 
            this.MnuExit.Image = global::Chatterbox.Properties.Resources.close;
            this.MnuExit.Name = "MnuExit";
            this.MnuExit.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.MnuExit.Size = new System.Drawing.Size(134, 22);
            this.MnuExit.Text = "Exit";
            this.MnuExit.Click += new System.EventHandler(this.MnuExit_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MnuCommands,
            this.MnuAbout});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // MnuCommands
            // 
            this.MnuCommands.Image = global::Chatterbox.Properties.Resources.commands;
            this.MnuCommands.Name = "MnuCommands";
            this.MnuCommands.ShortcutKeys = System.Windows.Forms.Keys.F10;
            this.MnuCommands.Size = new System.Drawing.Size(161, 22);
            this.MnuCommands.Text = "Commands";
            this.MnuCommands.Click += new System.EventHandler(this.MnuCommands_Click);
            // 
            // MnuAbout
            // 
            this.MnuAbout.Image = global::Chatterbox.Properties.Resources.about;
            this.MnuAbout.Name = "MnuAbout";
            this.MnuAbout.Size = new System.Drawing.Size(161, 22);
            this.MnuAbout.Text = "About";
            this.MnuAbout.Click += new System.EventHandler(this.MnuAbout_Click);
            // 
            // ImgInterface
            // 
            this.ImgInterface.Image = global::Chatterbox.Properties.Resources._interface;
            this.ImgInterface.Location = new System.Drawing.Point(4, 32);
            this.ImgInterface.Name = "ImgInterface";
            this.ImgInterface.Size = new System.Drawing.Size(950, 330);
            this.ImgInterface.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.ImgInterface.TabIndex = 7;
            this.ImgInterface.TabStop = false;
            // 
            // FrmChat
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ClientSize = new System.Drawing.Size(958, 371);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.LstUsers);
            this.Controls.Add(this.TxtMessage);
            this.Controls.Add(this.LstRooms);
            this.Controls.Add(this.RTxtFeed);
            this.Controls.Add(this.ImgInterface);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmChat";
            this.Text = "Chatterbox";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FrmMain_FormClosed);
            this.Load += new System.EventHandler(this.FrmMain_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ImgInterface)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox TxtMessage;
        private System.Windows.Forms.RichTextBox RTxtFeed;
        private System.Windows.Forms.ListBox LstUsers;
        private System.Windows.Forms.ListBox LstRooms;
        private System.Windows.Forms.PictureBox ImgInterface;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem MnuFile;
        private System.Windows.Forms.ToolStripMenuItem MnuExit;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MnuCommands;
        private System.Windows.Forms.ToolStripMenuItem MnuAbout;
    }
}

