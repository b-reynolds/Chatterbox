#pragma once
#include "command.h"

class CmdBlock : public Command
{
 
 public:

	 CmdBlock() : Command(Type::kBlock) {}

	 void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

