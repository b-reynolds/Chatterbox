#include "CmdMESSAGE.h"
#include <numeric>

void CmdMESSAGE::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	std::string message = getString(parameters);

	Room* room = user.getRoom();

	if(room == nullptr)
	{
		printf("\t(%d) %s > ALL : %s\n", user.getID(), user.getUsername().c_str(), message.c_str());
		for (int i = 0; i < users.size(); ++i)
		{
			if (users[i].getRoom() == nullptr)
			{
				user.sendMessage(users[i], user.getUsername() + ": " + message);
			}
		}
		sendMessage(user, statusToString(SUCCESS));
		return;
	}

	printf("\t(%d) %s > %s : %s\n", user.getID(), user.getUsername().c_str(), room->getName().c_str(), message.c_str());
	std::vector<User*> roomUsers = room->getUsers();

	for(int i = 0; i < roomUsers.size(); ++i)
	{
		if (user.getID() != roomUsers[i]->getID())
		{
			user.sendMessage(users[i], user.getUsername() + ": " + message);
		}
	}
	sendMessage(user, statusToString(SUCCESS));

}
