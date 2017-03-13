#pragma once
#include "command.h"

/*
* \brief Enter an existing room on the server. (E.g ENTER johns-room).
* If the destination room is locked, the correct password must be provided to enter.
*/
class CmdEnter : public Command
{

 public:

	CmdEnter() : Command(Type::kEnter) {}

	void execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

