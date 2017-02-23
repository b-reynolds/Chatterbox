using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Client
{
    internal class CmdRoom : Command
    {
        public override string execute(FrmMain form, string[] data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms)
        {
            if (data_parts.Length != 5)
            {
                return string.Empty;
            }

            bool room_exists = false;
            foreach (var r in rooms)
            {
                if (r.name() == data_parts[1])
                {
                    if (r.users() != Convert.ToUInt32(data_parts[2]))
                    {
                        r.set_users(Convert.ToUInt32(data_parts[2]));
                    }
                    room_exists = true;
                }
            }

            if (!room_exists)
            {
                rooms.Add(new Room(data_parts[1], Convert.ToUInt32(data_parts[2]), Convert.ToUInt32(data_parts[3]),
                    data_parts[4] == "yes"));
            }

            lst_rooms.BeginInvoke((MethodInvoker)delegate ()
                {
                    lst_rooms.Items.Clear();
                    foreach (var r in rooms)
                    {
                        lst_rooms.Items.Add(r.name() + " (" + r.users() + "/" + r.capacity() + ") " + (r.locked() ? "[*]" : ""));
                    }
                });

            return string.Empty;
        }

    }
}