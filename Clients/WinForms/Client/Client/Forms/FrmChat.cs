using System;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Forms;
using Chatterbox.Commands;

namespace Chatterbox.Forms
{
    public partial class FrmChat : Form
    {
        private const string kDisconnectMessage = @"Lost connection to the server.";

        private readonly ContextMenu menuUser;
        private readonly ContextMenu menuRoom;
        private readonly FrmConnect frmConnect;
        private readonly Client client;
        private readonly List<Room> rooms = new List<Room>();
        private readonly Queue<List<string>> cmdQueue = new Queue<List<string>>();

        private Thread thread;

        public FrmChat(ref Client client, FrmConnect frmConnect)
        {
            InitializeComponent();

            this.client = client;
            this.frmConnect = frmConnect;

            menuUser = new ContextMenu();
            var itemBlock = new MenuItem("Block/Unblock", BlockUser);
            menuUser.MenuItems.Add(itemBlock);

            menuRoom = new ContextMenu();
            var itemEnter = new MenuItem("Enter", EnterRoom);
            menuRoom.MenuItems.Add(itemEnter);
            var itemExit = new MenuItem("Exit", ExitRoom);
            menuRoom.MenuItems.Add(itemExit);
        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            thread = new Thread(ProcessData);
            thread.Start();
        }

        private void ProcessData()
        {
            while (true)
            {
                while(cmdQueue.Count != 0)
                {
                    var command = cmdQueue.Dequeue();
                    RTxtFeed.BeginInvoke((Action)(() => RTxtFeed.SelectedRtf = ProcessCommand(command)));
                }

                string data = client.GetData();

                if (data == null || !client.Connected())
                {
                    break;
                }  

                if (data == string.Empty)
                {
                    continue;
                }

                foreach(List<string> command in CmdUtil.SplitCommands(data))
                {
                    cmdQueue.Enqueue(command);
                }
            }

            BeginInvoke((MethodInvoker) delegate()
            {
                MessageBox.Show(kDisconnectMessage, Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                Close();
            });
        }

        private string ProcessCommand(List<string> command)
        {
            var cmd = CmdUtil.GetCommand(command[0]);
            return cmd == null ? string.Empty : cmd.execute(command, RTxtFeed, LstUsers, rooms, LstRooms);
        }

        private void TxtMessage_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                client.SendData(TxtMessage.Text);
                TxtMessage.Clear();
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
            client.Disconnect();
            frmConnect.Reset();
            frmConnect.Show();
        }

        private void BlockUser(object sender, EventArgs e)
        {
            string user = LstUsers.Items[LstUsers.SelectedIndex].ToString();
            client.SendData("block " + user);
        }

        private void EnterRoom(object sender, EventArgs e)
        {
            string room = LstRooms.Items[LstRooms.SelectedIndex].ToString();
            client.SendData("enter " + room);
        }

        private void ExitRoom(object sender, EventArgs e)
        {
            client.SendData("exit");
        }

        private void LstUsers_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Right)
            {
                return;
            }

            var item = LstUsers.IndexFromPoint(e.Location);

            if (item >= 0)
            {
                LstUsers.SelectedIndex = item;
                menuUser.Show(LstUsers, e.Location);
            }
        }

        private void LstRooms_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Right)
            {
                return;
            }

            var item = LstRooms.IndexFromPoint(e.Location);

            if (item >= 0)
            {
                LstRooms.SelectedIndex = item;
                menuRoom.Show(LstRooms, e.Location);
            }
        }
    }

}
