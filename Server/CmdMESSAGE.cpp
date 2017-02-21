#include "CmdMESSAGE.h"

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdMESSAGE::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if(!user.hasUsername())
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	// Ensure message is within the character limit

	std::string msg = buildString(parameters, ' ');
	size_t msgLen = msg.size();
	
	if(msgLen < MESSAGE_LENGTH_MIN)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_SHORT));
		return;
	}

	if(msgLen > MESSAGE_LENGTH_MAX)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_LONG));
		return;
	}

	Room* usrRoom = user.getRoom();
	std::string output = "MSG:" + user.getUsername() + ":" + msg;

	if(usrRoom != nullptr)
	{
		// Send message to room
		for(auto & otherUser : usrRoom->getUsers())
		{
			user.sendMessage(*otherUser, output);
		}
		printf("\t#%d %s > %s : %s\n", user.getID(), user.getUsername().c_str(), usrRoom->getName().c_str(), msg.c_str());
		sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
		return;
	}

	for(auto & otherUser : users)
	{
		// Send message to lobby
		if(otherUser.getRoom() == nullptr)
		{
			user.sendMessage(otherUser, output);
		}
	}

	printf("\t#%d %s : %s\n", user.getID(), user.getUsername().c_str(), msg.c_str());
	sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
}
