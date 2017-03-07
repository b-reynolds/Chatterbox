#pragma once
#include <vector>
#include "user.h"
#include "room.h"
#include "command_packet.h"

enum class Status
{
	kFail,
	kSuccess,
};

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
 * \brief Command Base Class
 */
class Command
{

 public:

	explicit Command(const Type &commandType) : type_(commandType) {}

	virtual ~Command() {}

	/* Pure virtual execute method implemented by all Commands */
	virtual void Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters) = 0;

	/* Converts a string to its CmdType equivalent */
	static Type StringToType(const std::string &string);

	/* Converts a CmdStatus to its string equivalent */
	static std::string StatusToString(const Status &status);

	Type type() const;

 protected:

	Type type_;

	/* Send data to a User */
	static void SendData(const User& user, const std::string& message);

	/* Builds a string by concatenating a vector of strings. Each string is prefixed with a joint. */
	static std::string BuildString(const std::vector<std::string>& strings, const char &joint);

};

