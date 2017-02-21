using System.Windows.Forms;

namespace Client
{
    internal class CmdConnect : Command
    {
        public override string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers)
        {
            if (dataParts.Length != 2)
            {
                return string.Empty;
            }

            return RTF_START + @"\i \b " + dataParts[1] + @"\b0  joined the server. \i0" + RTF_END;
        }
    }
}
