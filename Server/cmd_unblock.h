#pragma once
#include "command.h"

/*
* \brief Unblocks the user, enabling all communications to and from them. (E.g. BLOCK johnsmith).
* Users remain blocked until unblocked using the UNBLOCK command.
*/
class CmdUnblock : public Command
{

public:

	CmdUnblock() : Command(Type::kUnblock) {}

	void execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};

