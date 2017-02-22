#include "command.h"
#include <algorithm>
#include <assert.h>

/**
 * \brief Converts a string to its CmdType equivalent
 * \param string string
 */
Type Command::StringToType(const std::string& string)
{
	if (string == "UNAME")
		return Type::kUName;
	if (string == "MESSAGE")
		return Type::kMessage;
	if (string == "PM")
		return Type::kPm;
	if (string == "MKROOM")
		return Type::kMkRoom;
	if (string == "ENTER")
		return Type::kEnter;
	if (string == "EXIT")
		return Type::kExit;
	return Type::kNone;
}

/**
 * \brief Converts a CmdStatus to its string equivalent
 * \param cmdStatus cmdStatus
 */
std::string Command::StatusToString(const Status& status)
{
	switch (status)
	{
		case Status::kSuccess:
			return "$SUCCESS$";
		case Status::kInvalid:
			return "$ERR_INVALID$";
		case Status::kExists:
			return "$ERR_EXISTS$";
		case Status::kShort:
			return "$ERR_SHORT$";
		case Status::kLong:
			return "$ERR_LONG$";
		case Status::kIllegal:
			return "$ERR_ILLEGAL$";
		case Status::kRestricted:
			return "$ERR_RESTRICTED$";
		case Status::kNoUsr:
			return "$ERR_NOUSR$";
		case Status::kFull:
			return "$ERR_FULL$";
		case Status::kBadPass:
			return "$ERR_BADPASS$";
		default:
			return "FAIL";
	}
}

CommandPacket Command::StatusToPacket(const Status& status)
{
	switch(status)
	{
		case Status::kSuccess:
			return CommandPacket("SUCCESS");
		case Status::kInvalid:
			return CommandPacket("INVALID");
		case Status::kExists:
			return CommandPacket("EXISTS");
		case Status::kShort:
			return CommandPacket("SHORT");
		case Status::kLong:
			return CommandPacket("LONG");
		case Status::kIllegal:
			return CommandPacket("ILLEGAL");
		case Status::kRestricted:
			return CommandPacket("RESTRICTED");
		case Status::kNoUsr:
			return CommandPacket("NOUSR");
		case Status::kFull:
			return CommandPacket("FULL");
		case Status::kBadPass:
			return CommandPacket("BASPASS");
		default:
			assert(false);
	}
}

/**
 * \brief Returns the Command's CmdType
 */
Type Command::get_type() const
{
	return type_;
}

/**
* \brief Send a message to a User
* \param user recipient
* \param message message
*/
void Command::SendData(const User& user, const std::string& message)
{
	send(user.get_socket(), message.c_str(), static_cast<int>(message.length()), 0);
}

/**
* \brief Converts a string to lower case
* \param string string to convert
*/
std::string Command::ToLower(std::string string) const
{
	transform(string.begin(), string.end(), string.begin(), tolower);
	return string;
}

/**
* \brief Builds a string by concatenating a vector of strings. Each string is prefixed with a joint.
* \param strings strings to concatenate
* \param joint character to use as a joint
*/
std::string Command::BuildString(const std::vector<std::string>& strings, const char& joint)
{
	std::string string;
	for (int i = 0; i < strings.size(); ++i)
	{
		if (i != 0)
		{
			string += joint;
		}
		string += strings[i];
	}
	return string;
}

