using System.Collections.Generic;
using System.Linq;

namespace Chatterbox.Commands
{
    internal class CmdUtil
    {
        private const char kCommandSeperator = '$';
        private const char kParameterSeperator = '@';

        public static List<List<string>> SplitCommands(string input)
        {
            var split_commands = new List<List<string>>();
            var commands = input.Split(kCommandSeperator);

            foreach (string cmd in commands)
            {
                var cmd_parts = cmd.Split(kParameterSeperator);
                var command = cmd_parts.Where(part => part.Length != 0).ToList();
                if (command.Count > 0)
                {
                    split_commands.Add(command);
                }
            }

            return split_commands;
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
                case "CLEARROOMS":
                    return Command.CmdType.kClearRooms;
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
                case Command.CmdType.kError:
                    return new CmdError();
                case Command.CmdType.kInfo:
                    return new CmdInfo();
                case Command.CmdType.kClearRooms:
                    return new CmdClearRooms();
                default:
                    return null;
            }
        }
    }
}
