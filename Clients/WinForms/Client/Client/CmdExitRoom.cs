using System.Collections.Generic;
using System.Windows.Forms;

namespace Client
{
    internal class CmdExitRoom : Command
    {
        public override string execute(FrmMain form, string[] data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Length != 2)
            {
                return string.Empty;
            }

            return kRtfStart + @"\i \b " + data_parts[1] + @"\b0  left the room. \i0" + kRtfEnd;
        }
    }
}