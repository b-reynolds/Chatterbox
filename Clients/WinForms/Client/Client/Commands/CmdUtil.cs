using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Chatterbox.Commands
{
    internal class CmdUtil
    {
        public static List<List<string>> SplitCommands(string input)
        {
            var command_list = new List<List<string>>();
            string[] commands = input.Split(Command.kCommandSeperator);
            for (int i = 0; i < commands.Length; i++)
            {
                var command_parts = commands[i].Split(Command.kParameterSeperator);
                var command = command_parts.Where(t => t != string.Empty).ToList();
                if (command.Count > 0)
                {
                    command_list.Add(command);
                }
            }
            return command_list;
        }

        public static Command.CmdType StringToCmdType(string input)
        {
            switch (input)
            {
                case "MSG":
                    return Command.CmdType.kMsg;
                case "CONNECT":
                    return Command.CmdType.kConnect;
                case "CHANGE":
                    return Command.CmdType.kChange;
                case "PM":
                    return Command.CmdType.kPm;
                case "USERS":
                    return Command.CmdType.kUsers;
                case "DISCONNECT":
                    return Command.CmdType.kDisconnect;
                case "ROOM":
                    return Command.CmdType.kRoom;
                case "ENTERROOM":
                    return Command.CmdType.kEnterRoom;
                case "EXITROOM":
                    return Command.CmdType.kExitRoom;
                case "ERROR":
                    return Command.CmdType.kError;
                case "INFO":
                    return Command.CmdType.kInfo;
                default:
                    return Command.CmdType.kNone;
            }
        }

        public static Command GetCommand(string command)
        {
            switch (StringToCmdType(command))
            {
                case Command.CmdType.kMsg:
                    return new CmdMessage();
                case Command.CmdType.kConnect:
                    return new CmdConnect();
                case Command.CmdType.kChange:
                    return new CmdChange();
                case Command.CmdType.kPm:
                    return new CmdPM();
                case Command.CmdType.kUsers:
                    return new CmdUsers();
                case Command.CmdType.kDisconnect:
                    return new CmdDisconnect();
                case Command.CmdType.kRoom:
                    return new CmdRoom();
                case Command.CmdType.kEnterRoom:
                    return new CmdEnterRoom();
                case Command.CmdType.kExitRoom:
                    return new CmdExitRoom();
                case Command.CmdType.kError:
                    return new CmdError();
                case Command.CmdType.kInfo:
                    return new CmdInfo();
                default:
                    return null;
            }
        }
    }
}
