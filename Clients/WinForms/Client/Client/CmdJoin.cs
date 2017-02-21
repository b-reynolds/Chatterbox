using System.Windows.Forms;
using System;
using System.Threading.Tasks;

namespace Client
{
    internal class CmdJoin : Command
    {
        public override string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers)
        {
            if (dataParts.Length != 2)
            {
                return string.Empty;
            }

            //lstUsers.BeginInvoke((Action) (() => lstUsers.Items.Add(dataParts[1])));

            return RTF_START + @"\i \b " + dataParts[1] + @"\b0  joined the server. \i0" + RTF_END;
        }
    }
}
