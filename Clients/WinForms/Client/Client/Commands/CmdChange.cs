using System.Collections.Generic;
using System.Windows.Forms;

namespace Chatterbox.Commands
{
    internal class CmdChange : Command
    {
        public override string execute(List<string> data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Count != 3)
            {
                return string.Empty;
            }

            lst_users.BeginInvoke((MethodInvoker) delegate()
            {
                for (int i = lst_users.Items.Count - 1; i >= 0; --i)
                {
                    if (lst_users.Items[i].ToString() == data_parts[1])
                    {
                        lst_users.Items.RemoveAt(i);
                    }
                }
                lst_users.Items.Add(data_parts[2]);
            });

            return kRtfStart + @"\i \b " + data_parts[1] + @"\b0  changed their name to \b " + data_parts[2] + @". \b0 \i0" + kRtfEnd;
        }
    }
}
