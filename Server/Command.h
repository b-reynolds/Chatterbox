#pragma once
#include <vector>
#include "User.h"
#include "Room.h"

/*
 * \brief Enumeration of Command Statuses
 */
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

/**
 * \brief Enumeration of command types
 */
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

/**
 * \brief Command Base Class
 */
class Command
{

public:

	/* Constructor initializes commandType */
	explicit Command(const CmdType &commandType) : commandType(commandType) {}

	/* Virtual Destructor */
	virtual ~Command() {}

	virtual void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) = 0;

	/* Converts a string to its CmdType equivalent */
	static CmdType stringToCmdType(const std::string &string);

	/* Converts a CmdStatus to its string equivalent */
	static std::string cmdStatusToString(const CmdStatus &cmdStatus);

	/* Returns the Command's CmdType */
	CmdType getCommandType() const;

private:

	/* Command's CmdType */
	CmdType commandType;

	/* Send a message to a User */
	static void sendMessage(const User &user, const std::string &message);

	/* Converts a string to lower case */
	std::string toLower(std::string string) const;

	/* Builds a string by concatenating a vector of strings. Each string is prefixed with a joint. */
	static std::string buildString(const std::vector<std::string> &strings, const char &joint);

};

