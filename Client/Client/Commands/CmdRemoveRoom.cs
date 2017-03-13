using System.Collections.Generic;
using System.Windows.Forms;

namespace Chatterbox.Commands
{
    internal class CmdRemoveRoom : Command
    {
        public override string execute(List<string> data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Count != 2)
            {
                return string.Empty;
            }

            for (int i = 0; i < rooms.Count; i++)
            {
                if (rooms[i].name() == data_parts[1])
                {
                    rooms.RemoveAt(i);
                    break;
                }
            }       

            lst_rooms.BeginInvoke((MethodInvoker)delegate ()
             {
                lst_rooms.Items.Clear();

                 for (int i = 0; i < rooms.Count; i++)
                 {
                     lst_rooms.Items.Add(rooms[i].name() + " (" + rooms[i].users() + "/" + rooms[i].capacity() + ") " +
                                         (rooms[i].locked() ? "[*]" : ""));
                 }
            });

            return string.Empty;
        }
    }
}