using System;
using System.Windows.Forms;

namespace Client
{
    internal class CmdUsers : Command
    {
        public override string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers)
        {
            if (dataParts.Length > 1)
            {
                lstUsers.BeginInvoke((Action)(() => lstUsers.Items.Clear()));
                for (int i = 1; i < dataParts.Length - 1; i++)
                {
                    lstUsers.BeginInvoke((Action)(() => lstUsers.Items.Add(dataParts[i])));
                }
            }
            return string.Empty;
        }
    }
}