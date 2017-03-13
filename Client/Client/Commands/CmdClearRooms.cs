using System.Collections.Generic;
using System.Windows.Forms;

namespace Chatterbox.Commands
{
    internal class CmdClearRooms : Command
    {
        public override string execute(List<string> data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            lst_rooms.BeginInvoke((MethodInvoker)delegate ()
            {
                lst_rooms.Items.Clear();
            });

            return string.Empty;
        }
    }
}