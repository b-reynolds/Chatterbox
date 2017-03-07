using System;
using System.Windows.Forms;
using Client;

namespace Chatterbox
{
    public partial class FrmConnect : Form
    {
        private const string kIPDefault = "127.0.0.1";
        private const string kStatusDefault = "Waiting...";
        private const int kPortDefault = 47861;

        public FrmConnect()
        {
            InitializeComponent();
        }

        private void FrmConnect_Load(object sender, EventArgs e)
        {
            TxtIP.Text = kIPDefault;
            NudPort.Value = kPortDefault;
            set_status(kStatusDefault);
        }

        private void set_status(string status)
        {
            StsLabel.Text = status;
            Refresh();
        }

        private void set_controls_enabled(bool state)
        {
            TxtIP.Enabled = state;
            NudPort.Enabled = state;
            BtnConnect.Enabled = state;
        }

        public void reset()
        {
            set_controls_enabled(true);
            set_status(kStatusDefault);
        }

        private void BtnConnect_Click(object sender, EventArgs e)
        {
            set_controls_enabled(false);
            set_status("Connecting...");

            var client = new Client.Client(TxtIP.Text, Convert.ToInt32(NudPort.Value));

            if (!client.Connect())
            {
                set_controls_enabled(true);
                set_status("Connection Failed");
                return;
            }

            set_status("Connected");

            var frm_main = new FrmMain(ref client, this);
            frm_main.Show();

            Hide();
        }
    }
}
