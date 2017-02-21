using System.Windows.Forms;

namespace Client
{
    internal class CmdPM : Command
    {
        public override string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers)
        {
            if (dataParts.Length != 3)
            {
                return string.Empty;
            }
            return RTF_START + @"\i \cf2 (PM)\i0  [\b " + dataParts[1] + @"\b0 ] \cf1 : " + dataParts[2] + RTF_END;
        }
    }
}