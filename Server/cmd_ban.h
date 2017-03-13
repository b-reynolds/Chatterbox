#pragma once
#include "command.h"

/*
* \brief Bans a user from the room (E.g BAN john).
* An optional message can be supplied to give reasoning for the action.
*/
class CmdBan : public Command
{

public:

	CmdBan() : Command(Type::kBan) {}

	void execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

private:

	/* Accepted message length range */

	const unsigned int kMsgLengthMin = 1;
	const unsigned int kMsgLengthMax = 32;
};

