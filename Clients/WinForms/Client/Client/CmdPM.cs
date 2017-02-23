using System.Collections.Generic;
using System.Windows.Forms;

namespace Client
{
    internal class CmdPM : Command
    {
        public override string execute(FrmMain form, string[] data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Length != 3)
            {
                return string.Empty;
            }
            return kRtfStart + @"\i \cf2 (PM)\i0  [\b " + data_parts[1] + @"\b0 ] \cf1 : " + data_parts[2] + kRtfEnd;
        }
    }
}