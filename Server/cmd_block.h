#pragma once
#include "command.h"

/*
* \brief Block the user, disabling all communication to and from them. (E.g. BLOCK johnsmith).
* Users remain blocked until unblocked using the UNBLOCK command.
*/
class CmdBlock : public Command
{
 
 public:

	 CmdBlock() : Command(Type::kBlock) {}

	bool execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters) override;

};

