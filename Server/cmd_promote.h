#pragma once
#include "command.h"

class CmdPromote : public Command
{

public:

	CmdPromote() : Command(Type::kPromote) {};

	bool execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters) override;

};

