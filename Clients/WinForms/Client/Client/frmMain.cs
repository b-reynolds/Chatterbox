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

        private readonly Queue<string> command_queue_ = new Queue<string>();

        private readonly Client client_;
        private Thread thread_;

        private FrmConnect frm_connect_;

        private static IEnumerable<string> GetCommands(string input)
        {
            return input.Split('$').Where(part => part != Empty).ToList();
        }

        public FrmMain(ref Client client, FrmConnect frm_connect)
        {
            InitializeComponent();
            client_ = client;
            frm_connect_ = frm_connect;
        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            thread_ = new Thread(GetData);
            thread_.Start();
        }

        private void GetData()
        {
            while (true)
            {
                string data = client_.GetData();

                if (data != Empty)
                {
                    var commands = GetCommands(data);
                    foreach (string s in commands)
                    {
                        command_queue_.Enqueue(s);
                    }
                }

                if (data == null)
                {
                    Exit();
                    thread_.Abort();
                }

                if (command_queue_.Count != 0)
                {
                    string command = command_queue_.Dequeue();
                    LstCommands.BeginInvoke((Action)(() => LstCommands.Items.Add(command)));
                    UpdateFeed(ProcessData(command));
                }
            }
        }

        private string ProcessData(string data)
        {
            string[] dataParts = data.Split(':');

            var cmdType = Command.stringToCmdType(dataParts[0]);
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
                return command != null ? command.execute(dataParts, RTxtFeed, LstUsers) : Empty;
            }
            return Empty;
        }

        private void UpdateFeed(string message)
        {
           RTxtFeed.BeginInvoke((Action)(() => RTxtFeed.SelectedRtf = message));
        }

        private void Exit()
        {
            MessageBox.Show(@"Disconnected", @"Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            Application.Exit();
        }

        private void SendMessage()
        {
            client_.SendData(txtMessage.Text);
            txtMessage.Clear();
        }

        private void BtnSend_Click(object sender, EventArgs e)
        {
            SendMessage();
        }

        private void TxtMessage_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                BtnSend_Click(this, new EventArgs());
                e.SuppressKeyPress = true;
            }
        }

        private void RTxtFeed_TextChanged(object sender, EventArgs e)
        {
            RTxtFeed.SelectionStart = RTxtFeed.Text.Length;
            RTxtFeed.ScrollToCaret();
        }

        private void FrmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            client_.Disconnect();
            thread_.Abort();
            frm_connect_.Show();
        }
    }

}
