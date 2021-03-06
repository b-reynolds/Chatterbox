﻿using System.Collections.Generic;
using System.Windows.Forms;

namespace Chatterbox.Commands
{
    internal class CmdConnect : Command
    {
        public override string execute(List<string> data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Count != 2)
            {
                return string.Empty;
            }

            return kRtfStart + @"\i \b " + data_parts[1] + @"\b0  joined the server. \i0" + kRtfEnd;
        }
    }
}
