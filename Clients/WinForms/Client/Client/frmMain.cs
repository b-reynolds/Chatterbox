using System;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Threading;
using static System.String;

namespace Client
{
    public partial class FrmMain : Form
    {

        private delegate void UpdateFeedCallback(string message);

        public delegate string UpdateUserListCallback(string[] dataParts, ref RichTextBox rtxtFeed, ref ListBox lstUsers);

        private Client client;
        private Thread thread;

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
                if (data == null)
                {
                    exit();
                    thread.Abort();
                }
                updateFeed(processData(data));
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
                    case Command.CmdType.JOIN:
                        command = new CmdJoin();
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
                    default:
                        command = null;
                        break;
                }
                return command != null ? command.execute(dataParts, rtxtBody, lstUsers) : Empty;
            }

            //switch (dataParts[0])
            //{
            //    case "MSG":
            //        return dataParts[1] + ": " + dataParts[2] + Environment.NewLine;
            //    case "JOIN":
            //        return dataParts[1] + " joined the server." + Environment.NewLine;
            //    case "CHANGE":
            //        return dataParts[1] + " changed their name to " + dataParts[2] + Environment.NewLine;
            //    case "PM":
            //        return "(PM) " + dataParts[1] + ": " + dataParts[2] + Environment.NewLine;
            //    case "NROOM":
            //        if (lstRooms.InvokeRequired)
            //        {
            //            var updateRoomList = new UpdateRoomList(processData);
            //            Invoke(updateRoomList, "NROOM:" + dataParts[1]);
            //        }
            //        else
            //        {
            //            if (!lstRooms.Items.Contains(dataParts[1]))
            //            {
            //                lstRooms.Items.Add(dataParts[1]);
            //            }
            //        }
            //        break;
            //}

            return Empty;
        }

        private void updateFeed(string message)
        {
            if (rtxtBody.InvokeRequired)
            {
                var updateMessagesCallback = new UpdateFeedCallback(updateFeed);
                Invoke(updateMessagesCallback, message);
            }
            else
            {
                rtxtBody.SelectedRtf = message;
            }
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
    }

}
