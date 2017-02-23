using System.Collections.Generic;
using System.Windows.Forms;

namespace Client
{
    internal class CmdInfo : Command
    {
        public override string execute(FrmMain form, string[] data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms,
            ListBox lst_rooms)
        {
            if (data_parts.Length != 2)
            {
                return string.Empty;
            }

            return kRtfStart + @"\i \b Server:\b0  " + data_parts[1] + @" \i0" + kRtfEnd;
        }
    }
}