using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Client
{
    internal class CmdUsers : Command
    {
        public override string execute(FrmMain form, string[] data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Length <= 1)
            {
                return string.Empty;
            }

            lst_users.BeginInvoke((MethodInvoker) delegate ()
            {
                lst_users.Items.Clear();
                for (int i = 1; i < data_parts.Length; i++)
                {
                    lst_users.Items.Add(data_parts[i]);
                }
            });

            return string.Empty;
        }
    }
}