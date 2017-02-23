using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
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
            kRoom
        };

        public static CmdType StringToCmdType(string input)
        {
            switch (input)
            {
                case "MSG":
                    return CmdType.kMsg;
                case "CONNECT":
                    return CmdType.kConnect;
                case "CHANGE":
                    return CmdType.kChange;
                case "PM":
                    return CmdType.kPm;
                case "USERS":
                    return CmdType.kUsers;
                case "DISCONNECT":
                    return CmdType.kDisconnect;
                case "ROOM":
                    return CmdType.kRoom;
                default:
                    return CmdType.kNone;
            }
        }

        protected const string kRtfStart = @"{\rtf1\ansi\ansicpg1252\deff0\deflang1033\uc1 {\colortbl;\red0\green0\blue0;\red255\green0\blue0;}";
        protected const string kRtfEnd = @"\line}";

        public abstract string execute(FrmMain form, string[] data_parts, RichTextBox rtxt_feed, ListBox lst_users, List<Room> rooms, ListBox lst_rooms);
        
    }
}
