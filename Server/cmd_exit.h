#pragma once
#include "command.h"

class CmdExit : public Command
{

 public:

	CmdExit() : Command(Type::kExit) { ; }

	void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

