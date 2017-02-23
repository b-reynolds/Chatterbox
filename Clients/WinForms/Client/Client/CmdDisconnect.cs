using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Client
{
    internal class CmdDisconnect : Command
    {
        public override string execute(FrmMain form, string[] data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Length != 2)
            {
                return string.Empty;
            }

            lst_users.BeginInvoke((MethodInvoker) delegate ()
            {
                for (int i = lst_users.Items.Count - 1; i >= 0; --i)
                {
                    if (lst_users.Items[i].ToString() == data_parts[1])
                    {
                        lst_users.Items.RemoveAt(i);
                    }
                }
            });

            return kRtfStart + @"\i \b " + data_parts[1] + @"\b0  disconnected. \i0" + kRtfEnd;
        }
    }
}