#pragma once
#include "command.h"

class CmdPM : public Command
{

public:

	CmdPM() : Command(Type::kPm) {};

	void Execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

private:

	/* Accepted message length range */

	const int MESSAGE_LENGTH_MIN = 1;
	const int MESSAGE_LENGTH_MAX = 128;

};
