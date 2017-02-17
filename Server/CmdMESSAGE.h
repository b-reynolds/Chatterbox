#pragma once
#include "Command.h"

class CmdMESSAGE : public Command
{

public:

	CmdMESSAGE() : Command(MESSAGE) {};

	void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;
	

};

