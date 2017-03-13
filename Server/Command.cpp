#include "command.h"

/**
 * \brief Converts a string to its CmdType equivalent
 * \param string string
 */
Type Command::string_to_type(const std::string& string)
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
	if (string == "BLOCK")
		return Type::kBlock;
	if (string == "UNBLOCK")
		return Type::kUnblock;
	if (string == "PROMOTE")
		return Type::kPromote;
	return Type::kNone;
}


/**
 * \brief Returns the Command's type
 */
Type Command::type() const
{
	return type_;
}

/**
* \brief Send a message to a User
* \param user recipient
* \param message message
*/
void Command::send_data(const User& user, const std::string& message)
{
	send(user.socket(), message.c_str(), static_cast<int>(message.length()), 0);
}

/**
* \brief Builds a string by concatenating a vector of strings. Each string is prefixed with a joint.
* \param strings strings to concatenate
* \param joint character to use as a joint
*/
std::string Command::build_string(const std::vector<std::string>& strings, const char& joint)
{
	std::string string;
	for (unsigned int i = 0; i < strings.size(); ++i)
	{
		if (i != 0)
		{
			string += joint;
		}
		string += strings[i];
	}
	return string;
}

