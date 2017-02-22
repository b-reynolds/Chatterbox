#pragma once
#include "command.h"

/*
 * \brief Send a message (E.g Hello World).
 * Message is sent to users within the same room.
 * Messages must be between 1 and 128 characters long.
 */
class CmdMessage : public Command
{

 public:

	CmdMessage() : Command(Type::kMessage) {};
	
	void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;
	
 private:

	// Accepted message length range

	const int kMsgLengthMin = 1;
	const int kMsgLengthMax = 128;

};

