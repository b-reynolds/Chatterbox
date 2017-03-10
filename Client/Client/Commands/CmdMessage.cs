using System.Collections.Generic;
using System.Windows.Forms;

namespace Chatterbox.Commands
{
    internal class CmdMessage : Command
    {
        public override string execute(List<string> data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Count != 3)
            {
                return string.Empty;
            }
            return kRtfStart + @"\b [" + data_parts[1] + @"]\b0 : " + data_parts[2] + kRtfEnd;
        }
    }
}
