using System;
using System.Windows.Forms;

namespace Client
{
    public partial class FrmConnect : Form
    {
        private const string DEFAULT_HOSTNAME = "127.0.0.1";
        private const int DEFAULT_PORT = 47861;
        private const int DEFAULT_BUFFER_SIZE = 1024;

        public FrmConnect()
        {
            InitializeComponent();
        }

        private void FrmConnect_Load(object sender, EventArgs e)
        {
            txtHostname.Text = DEFAULT_HOSTNAME;
            nudPort.Value = DEFAULT_PORT;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            Enabled = false;

            string hostName = txtHostname.Text;
            int port = Convert.ToInt32(nudPort.Value);

            Client client = new Client(hostName, port, DEFAULT_BUFFER_SIZE);

            if (!client.connect())
            {
                MessageBox.Show(this, @"Connection failed.", @"Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Enabled = true;
                return;
            }

            FrmMain frmMain = new FrmMain(ref client);
            frmMain.Show();

            Hide();
        }

    }
}
