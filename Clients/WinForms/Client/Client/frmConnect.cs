using System;
using System.Windows.Forms;

namespace Client
{
    public partial class FrmConnect : Form
    {
        private const string kDefaultHostname = "127.0.0.1";
        private const int kDefaultPort = 47861;

        public FrmConnect()
        {
            InitializeComponent();
        }

        private void FrmConnect_Load(object sender, EventArgs e)
        {
            txtHostname.Text = kDefaultHostname;
            nudPort.Value = kDefaultPort;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            Enabled = false;

            string hostName = txtHostname.Text;
            int port = Convert.ToInt32(nudPort.Value);

            var client = new Client(hostName, port);

            if (!client.Connect())
            {
                MessageBox.Show(@"Connection failed!", Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                Enabled = true;
                return;
            }

            MessageBox.Show(@"Connected.", Text, MessageBoxButtons.OK, MessageBoxIcon.Information);

            var frmMain = new FrmMain(ref client, this);
            frmMain.Show();

            Hide();
            Enabled = true;

        }

    }
}
