using System;
using System.Windows.Forms;

namespace Client
{
    internal class CmdUsers : Command
    {
        public override string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers)
        {
            if (dataParts.Length <= 1)
            {
                return string.Empty;
            }

            lstUsers.BeginInvoke((MethodInvoker) delegate ()
            {
                lstUsers.Items.Clear();
                for (int i = 1; i < dataParts.Length; i++)
                {
                    lstUsers.Items.Add(dataParts[i]);
                }
            });

            return string.Empty;
        }
    }
}