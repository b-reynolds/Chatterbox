using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;
using static System.String;

namespace Client
{
    public partial class FrmMain : Form
    {

        private readonly Queue<string> qCommands = new Queue<string>();

        private readonly Client client;
        private Thread thread;

        private static IEnumerable<string> getCommands(string input)
        {
            return input.Split('$').Where(part => part != Empty).ToList();
        }

        public FrmMain(ref Client client)
        {
            InitializeComponent();
            this.client = client;
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            thread = new Thread(getData);
            thread.Start();
        }

        private void getData()
        {
            while (true)
            {
                string data = client.getData();

                if (data != Empty)
                {
                    IEnumerable<string> commands = getCommands(data);
                    foreach (string s in commands)
                    {
                        qCommands.Enqueue(s);
                    }
                }

                if (data == null)
                {
                    exit();
                    thread.Abort();
                }

                if (qCommands.Count != 0)
                {
                    string command = qCommands.Dequeue();
                    lstCommands.BeginInvoke((Action)(() => lstCommands.Items.Add(command)));
                    updateFeed(processData(command));
                }
            }
        }

        private string processData(string data)
        {
            string[] dataParts = data.Split(':');

            Command.CmdType cmdType = Command.stringToCmdType(dataParts[0]);
            if (cmdType != Command.CmdType.NONE)
            {
                Command command;
                switch (cmdType)
                {
                    case Command.CmdType.MSG:
                        command = new CmdMessage();
                        break;
                    case Command.CmdType.CONNECT:
                        command = new CmdConnect();
                        break;
                    case Command.CmdType.CHANGE:
                        command = new CmdChange();
                        break;
                        case Command.CmdType.PM:
                        command = new CmdPM();
                        break;
                    case Command.CmdType.USERS:
                        command = new CmdUsers();
                        break;
                    case Command.CmdType.DISCONNECT:
                        command = new CmdDisconnect();
                        break;  
                    default:
                        command = null;
                        break;
                }
                return command != null ? command.execute(dataParts, rtxtBody, lstUsers) : Empty;
            }
            return Empty;
        }

        private void updateFeed(string message)
        {
           rtxtBody.BeginInvoke((Action)(() => rtxtBody.SelectedRtf = message));
        }

        private void exit()
        {
            MessageBox.Show(@"Disconnected", @"Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            Application.Exit();
        }

        private void sendMessage()
        {
            client.sendData(txtMessage.Text);
            txtMessage.Clear();
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            sendMessage();
        }

        private void txtMessage_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                btnSend_Click(this, new EventArgs());
                e.SuppressKeyPress = true;
            }
        }

        private void rtxtBody_TextChanged(object sender, EventArgs e)
        {
            rtxtBody.SelectionStart = rtxtBody.Text.Length;
            rtxtBody.ScrollToCaret();
        }

    }

}
