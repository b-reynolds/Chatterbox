using System;
using System.Windows.Forms;
using Chatterbox.Commands;
using Chatterbox.Data_Types;
using Chatterbox.Forms;

namespace Chatterbox
{
    public partial class FrmConnect : Form
    {
        private const string kIPDefault = "127.0.0.1";
        private const string kStatusDefault = "Waiting...";
        private const string kStatusWorking = "Connecting...";
        private const string kStatusSuccess = "Connected.";
        private const string kStatusFail = "Connection Failed.";
        private const int kPortDefault = 47861;

        public FrmConnect()
        {
            InitializeComponent();
        }

        private void FrmConnect_Load(object sender, EventArgs e)
        {
            TxtIP.Text = kIPDefault;
            NudPort.Value = kPortDefault;
            SetStatus(kStatusDefault);
        }

        private void SetStatus(string status)
        {
            StsLabel.Text = status;
            Refresh();
        }

        private void SetControlsEnabled(bool state)
        {
            TxtIP.Enabled = state;
            NudPort.Enabled = state;
            BtnConnect.Enabled = state;
        }

        public void Reset()
        {
            SetControlsEnabled(true);
            SetStatus(kStatusDefault);
        }

        private void BtnConnect_Click(object sender, EventArgs e)
        {
            SetControlsEnabled(false);
            SetStatus(kStatusWorking);

            var client = new Client(TxtIP.Text, Convert.ToInt32(NudPort.Value));

            if (!client.Connect())
            {
                SetControlsEnabled(true);
                SetStatus(kStatusFail);
                return;
            }

            SetStatus(kStatusSuccess);

            var frmMain = new FrmChat(ref client, this);
            frmMain.Show();

            Hide();
        }

        private void MnuExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void MnuAbout_Click(object sender, EventArgs e)
        {
            var frmAbout = new FrmAbout();
            frmAbout.ShowDialog();
        }
    }
}
