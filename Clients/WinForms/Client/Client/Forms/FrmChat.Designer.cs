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
            this.ImgInterface = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.ImgInterface)).BeginInit();
            this.SuspendLayout();
            // 
            // TxtMessage
            // 
            this.TxtMessage.BackColor = System.Drawing.Color.White;
            this.TxtMessage.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.TxtMessage.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtMessage.ForeColor = System.Drawing.Color.Black;
            this.TxtMessage.Location = new System.Drawing.Point(18, 318);
            this.TxtMessage.Margin = new System.Windows.Forms.Padding(2);
            this.TxtMessage.Name = "TxtMessage";
            this.TxtMessage.Size = new System.Drawing.Size(771, 13);
            this.TxtMessage.TabIndex = 1;
            this.TxtMessage.KeyDown += new System.Windows.Forms.KeyEventHandler(this.TxtMessage_KeyDown);
            // 
            // RTxtFeed
            // 
            this.RTxtFeed.BackColor = System.Drawing.Color.White;
            this.RTxtFeed.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.RTxtFeed.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RTxtFeed.ForeColor = System.Drawing.Color.Black;
            this.RTxtFeed.Location = new System.Drawing.Point(223, 45);
            this.RTxtFeed.Margin = new System.Windows.Forms.Padding(2);
            this.RTxtFeed.Name = "RTxtFeed";
            this.RTxtFeed.Size = new System.Drawing.Size(566, 245);
            this.RTxtFeed.TabIndex = 3;
            this.RTxtFeed.Text = "";
            this.RTxtFeed.TextChanged += new System.EventHandler(this.RTxtFeed_TextChanged);
            // 
            // LstUsers
            // 
            this.LstUsers.BackColor = System.Drawing.Color.White;
            this.LstUsers.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.LstUsers.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LstUsers.ForeColor = System.Drawing.Color.Black;
            this.LstUsers.FormattingEnabled = true;
            this.LstUsers.IntegralHeight = false;
            this.LstUsers.Location = new System.Drawing.Point(18, 45);
            this.LstUsers.Margin = new System.Windows.Forms.Padding(2);
            this.LstUsers.Name = "LstUsers";
            this.LstUsers.Size = new System.Drawing.Size(181, 244);
            this.LstUsers.TabIndex = 4;
            this.LstUsers.MouseDown += new System.Windows.Forms.MouseEventHandler(this.LstUsers_MouseDown);
            // 
            // LstRooms
            // 
            this.LstRooms.BackColor = System.Drawing.Color.White;
            this.LstRooms.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.LstRooms.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LstRooms.ForeColor = System.Drawing.Color.Black;
            this.LstRooms.FormattingEnabled = true;
            this.LstRooms.IntegralHeight = false;
            this.LstRooms.Location = new System.Drawing.Point(813, 45);
            this.LstRooms.Margin = new System.Windows.Forms.Padding(2);
            this.LstRooms.Name = "LstRooms";
            this.LstRooms.Size = new System.Drawing.Size(181, 245);
            this.LstRooms.TabIndex = 6;
            this.LstRooms.MouseDown += new System.Windows.Forms.MouseEventHandler(this.LstRooms_MouseDown);
            // 
            // ImgInterface
            // 
            this.ImgInterface.Image = global::Chatterbox.Properties.Resources._interface;
            this.ImgInterface.Location = new System.Drawing.Point(2, 7);
            this.ImgInterface.Name = "ImgInterface";
            this.ImgInterface.Size = new System.Drawing.Size(1008, 341);
            this.ImgInterface.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.ImgInterface.TabIndex = 7;
            this.ImgInterface.TabStop = false;
            // 
            // FrmChat
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ClientSize = new System.Drawing.Size(1015, 354);
            this.Controls.Add(this.LstUsers);
            this.Controls.Add(this.TxtMessage);
            this.Controls.Add(this.LstRooms);
            this.Controls.Add(this.RTxtFeed);
            this.Controls.Add(this.ImgInterface);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmChat";
            this.Text = "Chatterbox";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FrmMain_FormClosed);
            this.Load += new System.EventHandler(this.FrmMain_Load);
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
    }
}

