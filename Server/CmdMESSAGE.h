#pragma once
#include "Command.h"

/*
 * \brief Send a message.
 * Message is sent to users within the same room.
 * Messages must be between 1 and 128 characters long.
 */
class CmdMESSAGE : public Command
{

public:

	/* Default Constructor */
	CmdMESSAGE() : Command(CmdType::MESSAGE) {};
	
	/* Execute command */
	void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;
	
private:

	/* Accepted message length range */

	const int MESSAGE_LENGTH_MIN = 1;
	const int MESSAGE_LENGTH_MAX = 128;

};

