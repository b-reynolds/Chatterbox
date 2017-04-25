#pragma once
#include "command.h"

/*
* \brief Removes a user from the room (E.g KICK john).
* An optional message can be supplied to give reasoning for the action.
*/
class CmdKick : public Command
{

public:

	CmdKick() : Command(Type::kKick) {}

	bool execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters) override;

private:

	/* Accepted message length range */

	const unsigned int kMsgLengthMin = 1;
	const unsigned int kMsgLengthMax = 32;

};
