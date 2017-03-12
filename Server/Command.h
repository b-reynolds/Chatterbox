#pragma once
#include <vector>
#include "user.h"
#include "room.h"

/* Enumeration of Statuses */
enum class Status
{
	kFail,
	kSuccess,
};

/* Emumeration of command types */
enum class Type
{
	kNone,
	kUName,
	kMessage,
	kPm,
	kMkRoom,
	kEnter,
	kExit,
	kBlock,
	kUnblock,
};

/**
 * \brief Abstract command base class
 */
class Command
{

 public:

	/* Consructor sets the command type */
	explicit Command(const Type &commandType) : type_(commandType) {}

	/* Virtual deconstructor */
	virtual ~Command() = default;

	/* Pure virtual execute method implemented by all Commands */
	virtual void Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters) = 0;

	/* Converts a string to its CmdType equivalent */
	static Type StringToType(const std::string &string);

	/* Converts a CmdStatus to its string equivalent */
	static std::string StatusToString(const Status &status);

	/* Returns the command type */
	Type type() const;

 protected:

	/* Command type */
	Type type_;

	/* Send data to a User */
	static void SendData(const User& user, const std::string& message);

	/* Builds a string by concatenating a vector of strings. Each string is prefixed with a joint. */
	static std::string BuildString(const std::vector<std::string>& strings, const char &joint);

};

