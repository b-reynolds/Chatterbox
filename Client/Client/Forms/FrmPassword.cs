using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Chatterbox.Forms
{
    public partial class FrmPassword : Form
    {
        private readonly FrmChat frmChat;
        private readonly string room;

        public FrmPassword(FrmChat frmChat, string room)
        {
            InitializeComponent();
            this.frmChat = frmChat;
            this.room = room;
        }

        private void TxtMessage_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                e.Handled = true;
                e.SuppressKeyPress = true;
                frmChat.EnterRoom(room, TxtMessage.Text);
                Close();
            }
        }

        private void FrmPassword_Load(object sender, EventArgs e)
        {

        }
    }
}
