#pragma once
#include "command.h"

/*
* \brief Exits the current room (if any) and return the user to the lobby.(E.g EXIT).
*/
class CmdExit : public Command
{

 public:

	CmdExit() : Command(Type::kExit) { ; }

	void execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

