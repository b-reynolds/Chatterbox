#include "CmdMESSAGE.h"
#include <numeric>

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdMESSAGE::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure message is within the character limit

	std::string msg = buildString(parameters, ' ');
	size_t msgLen = msg.size();
	
	if(msgLen < MESSAGE_LENGTH_MIN)
	{
		sendMessage(user, statusToString(ERR_SHORT));
		return;
	}

	if(msgLen > MESSAGE_LENGTH_MAX)
	{
		sendMessage(user, statusToString(ERR_LONG));
		return;
	}

	Room* usrRoom = user.getRoom();

	if(usrRoom != nullptr)
	{
		// Send message to room
		for(auto & otherUser : usrRoom->getUsers())
		{
			user.sendMessage(*otherUser, user.getUsername() + ": " + msg);
		}
		printf("\t#%d %s > %s : %s\n", user.getID(), user.getUsername().c_str(), usrRoom->getName().c_str(), msg.c_str());
		sendMessage(user, statusToString(SUCCESS));
		return;
	}

	for(auto & otherUser : users)
	{
		// Send message to lobby
		if(user.getRoom() == nullptr)
		{
			user.sendMessage(otherUser, user.getUsername() + ": " + msg);
		}
	}

	printf("\t#%d %s : %s\n", user.getID(), user.getUsername().c_str(), msg.c_str());
	sendMessage(user, statusToString(SUCCESS));
}
