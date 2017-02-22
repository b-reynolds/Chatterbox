#pragma once
#include "command.h"

class CmdEXIT : public Command
{

public:

	CmdEXIT() : Command(Type::kExit) { ; }

	void Execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

