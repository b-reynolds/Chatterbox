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
	if (string == "KICK")
		return Type::kKick;
	if (string == "BAN")
		return Type::kBan;
	if (string == "UNBAN")
		return Type::kUnban;
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