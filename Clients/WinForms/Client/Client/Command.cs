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
            MSG,
            CONNECT,
            CHANGE,
            PM,
            NONE,
            USERS,
            DISCONNECT
        };

        public static CmdType stringToCmdType(string input)
        {
            switch (input)
            {
                case "MSG":
                    return CmdType.MSG;
                case "CONNECT":
                    return CmdType.CONNECT;
                case "CHANGE":
                    return CmdType.CHANGE;
                case "PM":
                    return CmdType.PM;
                case "USERS":
                    return CmdType.USERS;
                case "DISCONNECT":
                    return CmdType.DISCONNECT;
                default:
                    return CmdType.NONE;
            }
        }

        protected const string RTF_START = @"{\rtf1\ansi\ansicpg1252\deff0\deflang1033\uc1 {\colortbl;\red0\green0\blue0;\red255\green0\blue0;}";
        protected const string RTF_END = @"\line}";

        public abstract string execute(string[] dataParts, RichTextBox rtxtFeed, ListBox lstUsers);
        
    }
}
