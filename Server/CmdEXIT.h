#pragma once
#include "Command.h"

class CmdEXIT : public Command
{

public:

	CmdEXIT() : Command(CmdType::EXIT) { ; }

	void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

