#pragma once
#include "command.h"

class CmdUnblock : public Command
{

public:

	CmdUnblock() : Command(Type::kUnblock) {}

	void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

