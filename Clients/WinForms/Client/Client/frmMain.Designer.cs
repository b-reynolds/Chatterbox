namespace Client {
    partial class FrmMain {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmMain));
            this.btnSend = new System.Windows.Forms.Button();
            this.txtMessage = new System.Windows.Forms.TextBox();
            this.RTxtFeed = new System.Windows.Forms.RichTextBox();
            this.LstUsers = new System.Windows.Forms.ListBox();
            this.TblLayout = new System.Windows.Forms.TableLayoutPanel();
            this.llbUsers = new System.Windows.Forms.Label();
            this.lblMessages = new System.Windows.Forms.Label();
            this.lblRooms = new System.Windows.Forms.Label();
            this.lstRooms = new System.Windows.Forms.ListBox();
            this.LstCommands = new System.Windows.Forms.ListBox();
            this.lblCommands = new System.Windows.Forms.Label();
            this.TblLayout.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnSend
            // 
            this.btnSend.AutoSize = true;
            this.btnSend.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnSend.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnSend.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSend.Location = new System.Drawing.Point(676, 375);
            this.btnSend.Margin = new System.Windows.Forms.Padding(2);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(164, 23);
            this.btnSend.TabIndex = 0;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.BtnSend_Click);
            // 
            // txtMessage
            // 
            this.txtMessage.BackColor = System.Drawing.Color.White;
            this.txtMessage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TblLayout.SetColumnSpan(this.txtMessage, 2);
            this.txtMessage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtMessage.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtMessage.ForeColor = System.Drawing.Color.Black;
            this.txtMessage.Location = new System.Drawing.Point(2, 375);
            this.txtMessage.Margin = new System.Windows.Forms.Padding(2);
            this.txtMessage.Name = "txtMessage";
            this.txtMessage.Size = new System.Drawing.Size(670, 22);
            this.txtMessage.TabIndex = 1;
            this.txtMessage.KeyDown += new System.Windows.Forms.KeyEventHandler(this.TxtMessage_KeyDown);
            // 
            // RTxtFeed
            // 
            this.RTxtFeed.BackColor = System.Drawing.Color.White;
            this.RTxtFeed.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RTxtFeed.Dock = System.Windows.Forms.DockStyle.Fill;
            this.RTxtFeed.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RTxtFeed.ForeColor = System.Drawing.Color.Black;
            this.RTxtFeed.Location = new System.Drawing.Point(170, 24);
            this.RTxtFeed.Margin = new System.Windows.Forms.Padding(2);
            this.RTxtFeed.Name = "RTxtFeed";
            this.RTxtFeed.Size = new System.Drawing.Size(502, 347);
            this.RTxtFeed.TabIndex = 3;
            this.RTxtFeed.Text = "";
            this.RTxtFeed.TextChanged += new System.EventHandler(this.RTxtFeed_TextChanged);
            // 
            // LstUsers
            // 
            this.LstUsers.BackColor = System.Drawing.Color.White;
            this.LstUsers.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.LstUsers.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LstUsers.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LstUsers.ForeColor = System.Drawing.Color.Black;
            this.LstUsers.FormattingEnabled = true;
            this.LstUsers.IntegralHeight = false;
            this.LstUsers.ItemHeight = 14;
            this.LstUsers.Location = new System.Drawing.Point(2, 24);
            this.LstUsers.Margin = new System.Windows.Forms.Padding(2);
            this.LstUsers.Name = "LstUsers";
            this.LstUsers.Size = new System.Drawing.Size(164, 347);
            this.LstUsers.TabIndex = 4;
            // 
            // TblLayout
            // 
            this.TblLayout.ColumnCount = 4;
            this.TblLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.TblLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 45F));
            this.TblLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.TblLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.TblLayout.Controls.Add(this.LstUsers, 0, 1);
            this.TblLayout.Controls.Add(this.txtMessage, 0, 2);
            this.TblLayout.Controls.Add(this.llbUsers, 0, 0);
            this.TblLayout.Controls.Add(this.lblMessages, 1, 0);
            this.TblLayout.Controls.Add(this.lblRooms, 2, 0);
            this.TblLayout.Controls.Add(this.RTxtFeed, 1, 1);
            this.TblLayout.Controls.Add(this.lstRooms, 2, 1);
            this.TblLayout.Controls.Add(this.LstCommands, 3, 1);
            this.TblLayout.Controls.Add(this.lblCommands, 3, 0);
            this.TblLayout.Controls.Add(this.btnSend, 2, 2);
            this.TblLayout.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TblLayout.Location = new System.Drawing.Point(0, 0);
            this.TblLayout.Margin = new System.Windows.Forms.Padding(2);
            this.TblLayout.Name = "TblLayout";
            this.TblLayout.RowCount = 3;
            this.TblLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 5.921052F));
            this.TblLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 94.07895F));
            this.TblLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.TblLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.TblLayout.Size = new System.Drawing.Size(1125, 400);
            this.TblLayout.TabIndex = 5;
            // 
            // llbUsers
            // 
            this.llbUsers.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.llbUsers.AutoSize = true;
            this.llbUsers.ForeColor = System.Drawing.Color.Black;
            this.llbUsers.Location = new System.Drawing.Point(3, 4);
            this.llbUsers.Name = "llbUsers";
            this.llbUsers.Size = new System.Drawing.Size(43, 14);
            this.llbUsers.TabIndex = 8;
            this.llbUsers.Text = "Users";
            // 
            // lblMessages
            // 
            this.lblMessages.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lblMessages.AutoSize = true;
            this.lblMessages.ForeColor = System.Drawing.Color.Black;
            this.lblMessages.Location = new System.Drawing.Point(171, 4);
            this.lblMessages.Name = "lblMessages";
            this.lblMessages.Size = new System.Drawing.Size(70, 14);
            this.lblMessages.TabIndex = 7;
            this.lblMessages.Text = "Messages";
            // 
            // lblRooms
            // 
            this.lblRooms.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lblRooms.AutoSize = true;
            this.lblRooms.ForeColor = System.Drawing.Color.Black;
            this.lblRooms.Location = new System.Drawing.Point(677, 4);
            this.lblRooms.Name = "lblRooms";
            this.lblRooms.Size = new System.Drawing.Size(49, 14);
            this.lblRooms.TabIndex = 9;
            this.lblRooms.Text = "Rooms";
            // 
            // lstRooms
            // 
            this.lstRooms.BackColor = System.Drawing.Color.White;
            this.lstRooms.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lstRooms.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstRooms.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lstRooms.ForeColor = System.Drawing.Color.Black;
            this.lstRooms.FormattingEnabled = true;
            this.lstRooms.IntegralHeight = false;
            this.lstRooms.ItemHeight = 14;
            this.lstRooms.Location = new System.Drawing.Point(676, 24);
            this.lstRooms.Margin = new System.Windows.Forms.Padding(2);
            this.lstRooms.Name = "lstRooms";
            this.lstRooms.Size = new System.Drawing.Size(164, 347);
            this.lstRooms.TabIndex = 6;
            // 
            // LstCommands
            // 
            this.LstCommands.BackColor = System.Drawing.Color.White;
            this.LstCommands.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.LstCommands.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LstCommands.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LstCommands.ForeColor = System.Drawing.Color.Black;
            this.LstCommands.FormattingEnabled = true;
            this.LstCommands.IntegralHeight = false;
            this.LstCommands.ItemHeight = 14;
            this.LstCommands.Location = new System.Drawing.Point(844, 24);
            this.LstCommands.Margin = new System.Windows.Forms.Padding(2);
            this.LstCommands.Name = "LstCommands";
            this.TblLayout.SetRowSpan(this.LstCommands, 2);
            this.LstCommands.Size = new System.Drawing.Size(279, 374);
            this.LstCommands.TabIndex = 5;
            // 
            // lblCommands
            // 
            this.lblCommands.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lblCommands.AutoSize = true;
            this.lblCommands.ForeColor = System.Drawing.Color.Black;
            this.lblCommands.Location = new System.Drawing.Point(845, 4);
            this.lblCommands.Name = "lblCommands";
            this.lblCommands.Size = new System.Drawing.Size(137, 14);
            this.lblCommands.TabIndex = 10;
            this.lblCommands.Text = "Commands Recieved";
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(1125, 400);
            this.Controls.Add(this.TblLayout);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmMain";
            this.Text = "bChat";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FrmMain_FormClosed);
            this.Load += new System.EventHandler(this.FrmMain_Load);
            this.TblLayout.ResumeLayout(false);
            this.TblLayout.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.TextBox txtMessage;
        private System.Windows.Forms.RichTextBox RTxtFeed;
        private System.Windows.Forms.ListBox LstUsers;
        private System.Windows.Forms.TableLayoutPanel TblLayout;
        private System.Windows.Forms.ListBox LstCommands;
        private System.Windows.Forms.ListBox lstRooms;
        private System.Windows.Forms.Label lblMessages;
        private System.Windows.Forms.Label llbUsers;
        private System.Windows.Forms.Label lblRooms;
        private System.Windows.Forms.Label lblCommands;
    }
}

