using System.Windows.Forms;

namespace Client
{
    internal class CmdMessage : Command
    {
        public override string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers)
        {
            if (dataParts.Length != 3)
            {
                return string.Empty;
            }
            return RTF_START + @"\b [" + dataParts[1] + @"]\b0 : " + dataParts[2] + RTF_END;
        }
    }
}
