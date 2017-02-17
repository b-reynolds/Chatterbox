#include "Command.h"
#include <algorithm>

void Command::sendMessage(const User& user, const std::string& message) const
{
	send(user.getSocket(), message.c_str(), static_cast<int>(message.length()), 0);
}

/**
 * \brief Converts a string to lower case
 * \param string string to convert
 */
std::string Command::toLower(std::string string) const
{
	transform(string.begin(), string.end(), string.begin(), tolower);
	return string;
}

/**
 * \brief Builds a string by concatenating a vector of strings. Each string is prefixed with a joint.
 * \param strings strings to concatenate
 * \param joint character to use as a joint
 */
std::string Command::buildString(const std::vector<std::string>& strings, const char& joint) const
{
	std::string string;
	for(int i = 0; i < strings.size(); ++i)
	{
		if(i != 0)
		{
			string += joint;
		}
		string += strings[i];
	}
	return string;
}

CmdType Command::stringToCmdType(const std::string& string)
{
	if (string == "UNAME")
		return CmdType::UNAME;
	if (string == "MESSAGE")
		return CmdType::MESSAGE;
	if (string == "PM")
		return CmdType::PM;
	if (string == "MKROOM")
		return CmdType::MKROOM;
	if (string == "ENTER")
		return CmdType::ENTER;
	if (string == "EXIT")
		return CmdType::EXIT;
	return CmdType::NONE;
}

std::string Command::cmdStatusToString(const CmdStatus& cmdStatus)
{
	switch (cmdStatus)
	{
		case CmdStatus::SUCCESS:
			return "SUCCESS";
		case CmdStatus::ERR_INVALID:
			return "ERR_INVALID";
		case CmdStatus::ERR_EXISTS:
			return "ERR_EXISTS";
		case CmdStatus::ERR_SHORT:
			return "ERR_SHORT";
		case CmdStatus::ERR_LONG:
			return "ERR_LONG";
		case CmdStatus::ERR_ILLEGAL:
			return "ERR_ILLEGAL";
		case CmdStatus::ERR_RESTRICTED:
			return "ERR_RESTRICTED";
		case CmdStatus::ERR_NOUSR:
			return "ERR_NOUSR";
		default:
			return "FAIL";
	}
}

CmdType Command::getCommandType() const
{
	return commandType;
}
