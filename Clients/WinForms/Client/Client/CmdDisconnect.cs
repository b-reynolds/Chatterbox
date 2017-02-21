using System;
using System.Windows.Forms;

namespace Client
{
    internal class CmdDisconnect : Command
    {
        public override string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers)
        {
            if (dataParts.Length != 2)
            {
                return string.Empty;
            }

            lstUsers.BeginInvoke((MethodInvoker) delegate ()
            {
                for (int i = lstUsers.Items.Count - 1; i >= 0; --i)
                {
                    if (lstUsers.Items[i].ToString() == dataParts[1])
                    {
                        lstUsers.Items.RemoveAt(i);
                    }
                }
            });

            return RTF_START + @"\i \b " + dataParts[1] + @"\b0  disconnected. \i0" + RTF_END;
        }
    }
}