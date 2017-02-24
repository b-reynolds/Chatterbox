#pragma once
#include "command.h"

class CmdEnter : public Command
{

 public:

	CmdEnter() : Command(Type::kEnter) {}

	void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

