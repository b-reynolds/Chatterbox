#pragma once
#include "Command.h"

class CmdUNAME : public Command
{

public:

	CmdUNAME() : Command(UNAME) {};

	void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

private:

	const int USERNAME_LENGTH_MIN = 3;
	const int USERNAME_LENGTH_MAX = 12;

};

