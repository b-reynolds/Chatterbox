#pragma once
#include "Error.h"
#include <vector>
#include "User.h"
#include "Room.h"



class Command
{

public:
	virtual ~Command()
	{
	}

	explicit Command(const CommandType &commandType) : commandType(commandType) {}

	virtual void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) = 0;

	void sendMessage(const User &user, const std::string &message) const;

	std::string convertToLower(const std::string &string) const;

	std::string getString(const std::vector<std::string> &strings) const;

	CommandType getCommandType() const;

private:

	CommandType commandType;

};

struct BindStrings
{
	std::string operator()(const std::string &string, const std::string &other) const
	{
		return string.empty() ? other : string + " " + other;
	}
};
