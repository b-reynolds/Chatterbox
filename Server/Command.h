#pragma once
#include <vector>
#include "User.h"
#include "Room.h"

enum class CmdStatus
{
	FAIL,
	SUCCESS,
	ERR_INVALID,
	ERR_EXISTS,
	ERR_SHORT,
	ERR_LONG,
	ERR_ILLEGAL,
	ERR_RESTRICTED,
	ERR_NOUSR
};

enum class CmdType
{
	NONE,
	UNAME,
	MESSAGE,
	PM,
	MKROOM,
	ENTER,
	EXIT
};


class Command
{

public:

	explicit Command(const CmdType &commandType) : commandType(commandType) {}
	virtual ~Command() {}

	virtual void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) = 0;

	void sendMessage(const User &user, const std::string &message) const;

	/* Converts a string to lower case */
	std::string toLower(std::string string) const;

	/* Builds a string by concatenating a vector of strings. Each string is prefixed with a joint. */
	std::string buildString(const std::vector<std::string> &strings, const char &joint) const;

	static CmdType stringToCmdType(const std::string &string);
	static std::string cmdStatusToString(const CmdStatus &cmdStatus);

	CmdType getCommandType() const;

private:

	CmdType commandType;

};

