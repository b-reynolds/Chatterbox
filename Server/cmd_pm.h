#pragma once
#include "command.h"

/*
* \brief Send a private message (E.g PM John Hello World).
* Message is sent to the specified recipient.
* Messages must be between 1 and 128 characters long.
*/
class CmdPm : public Command
{

 public:

	CmdPm() : Command(Type::kPm) {};

	void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

 private:

	// Accepted message length range

	const int kMsgLengthMin = 1;
	const int kMsgLengthMax = 128;

};
