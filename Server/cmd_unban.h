#pragma once
#include "command.h"

/*
* \brief Unbans a user from the room (E.g UNBAN john).
*/
class CmdUnban : public Command
{

public:

	CmdUnban() : Command(Type::kUnban) {}

	bool execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters) override;

};

