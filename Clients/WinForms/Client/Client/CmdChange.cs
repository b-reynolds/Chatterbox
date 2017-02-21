﻿using System.Windows.Forms;

namespace Client
{
    internal class CmdChange : Command
    {
        public override string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers)
        {
            if (dataParts.Length != 3)
            {
                return string.Empty;
            }

            lstUsers.BeginInvoke((MethodInvoker) delegate()
            {
                for (int i = lstUsers.Items.Count - 1; i >= 0; --i)
                {
                    if (lstUsers.Items[i].ToString() == dataParts[1])
                    {
                        lstUsers.Items.RemoveAt(i);
                    }
                }
                lstUsers.Items.Add(dataParts[2]);
            });

            return RTF_START + @"\i \b " + dataParts[1] + @"\b0  changed their name to \b " + dataParts[2] + @". \b0 \i0" + RTF_END;
        }
    }
}
