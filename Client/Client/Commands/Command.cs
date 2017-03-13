using System.Collections.Generic;
using System.Windows.Forms;
using Chatterbox.Forms;

namespace Chatterbox.Commands
{
    internal abstract class Command
    {
        public enum CmdType
        {
            kMsg,
            kConnect,
            kChange,
            kPm,
            kNone,
            kUsers,
            kDisconnect,
            kRoom,
            kExitRoom,
            kError,
            kInfo,
            kClearRooms
        };

        protected const string kRtfStart = @"{\rtf1\ansi\ansicpg1252\deff0\deflang1033\uc1 {\colortbl;\red0\green0\blue0;\red255\green0\blue0;}";
        protected const string kRtfEnd = @"\line}";

        public abstract string execute(List<string> data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms);
        
    }
}
