using System.Collections.Generic;
using System.Windows.Forms;

namespace Chatterbox.Commands
{
    internal class CmdError : Command
    {
        public override string execute(List<string> data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms,
            ListBox lst_rooms)
        {
            if (data_parts.Count != 2)
            {
                return string.Empty;
            }

            return kRtfStart + @"\cf2 \i \b [Error]: \b0 \cf1 " + data_parts[1] + @" \i0" + kRtfEnd;
        }
    }
}