namespace Chatterbox
{
    partial class FrmAbout
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmAbout));
            this.ImgLogo = new System.Windows.Forms.PictureBox();
            this.lblDescription = new System.Windows.Forms.Label();
            this.BtnClose = new System.Windows.Forms.Button();
            this.LblGitHub = new System.Windows.Forms.LinkLabel();
            ((System.ComponentModel.ISupportInitialize)(this.ImgLogo)).BeginInit();
            this.SuspendLayout();
            // 
            // ImgLogo
            // 
            this.ImgLogo.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ImgLogo.Image = ((System.Drawing.Image)(resources.GetObject("ImgLogo.Image")));
            this.ImgLogo.Location = new System.Drawing.Point(12, 9);
            this.ImgLogo.Name = "ImgLogo";
            this.ImgLogo.Size = new System.Drawing.Size(380, 48);
            this.ImgLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.ImgLogo.TabIndex = 6;
            this.ImgLogo.TabStop = false;
            // 
            // lblDescription
            // 
            this.lblDescription.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblDescription.Location = new System.Drawing.Point(12, 67);
            this.lblDescription.Name = "lblDescription";
            this.lblDescription.Size = new System.Drawing.Size(385, 32);
            this.lblDescription.TabIndex = 7;
            this.lblDescription.Text = "A simple chat client written in C# for use with the Chatterbox Server. ";
            // 
            // BtnClose
            // 
            this.BtnClose.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnClose.Location = new System.Drawing.Point(12, 130);
            this.BtnClose.Name = "BtnClose";
            this.BtnClose.Size = new System.Drawing.Size(385, 29);
            this.BtnClose.TabIndex = 8;
            this.BtnClose.Text = "Close";
            this.BtnClose.UseVisualStyleBackColor = true;
            this.BtnClose.Click += new System.EventHandler(this.BtnClose_Click);
            // 
            // LblGitHub
            // 
            this.LblGitHub.AutoSize = true;
            this.LblGitHub.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LblGitHub.LinkBehavior = System.Windows.Forms.LinkBehavior.AlwaysUnderline;
            this.LblGitHub.Location = new System.Drawing.Point(87, 104);
            this.LblGitHub.Name = "LblGitHub";
            this.LblGitHub.Size = new System.Drawing.Size(239, 13);
            this.LblGitHub.TabIndex = 10;
            this.LblGitHub.TabStop = true;
            this.LblGitHub.Text = "https://github.com/b-reynolds";
            this.LblGitHub.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.LblGitHub_LinkClicked);
            // 
            // FrmAbout
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(409, 168);
            this.Controls.Add(this.LblGitHub);
            this.Controls.Add(this.BtnClose);
            this.Controls.Add(this.lblDescription);
            this.Controls.Add(this.ImgLogo);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmAbout";
            this.Text = "About";
            ((System.ComponentModel.ISupportInitialize)(this.ImgLogo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox ImgLogo;
        private System.Windows.Forms.Label lblDescription;
        private System.Windows.Forms.Button BtnClose;
        private System.Windows.Forms.LinkLabel LblGitHub;
    }
}