#include "CmdEXIT.h"

void CmdEXIT::execute(User& user, const std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(user.getRoom() == nullptr)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	Room* room = user.getRoom();
	std::vector<User*> roomUsers = room->getUsers();

	for(int i = 0; i < roomUsers.size(); ++i)
	{
		if(roomUsers[i]->getID() == user.getID())
		{
			roomUsers.erase(roomUsers.begin() + i);
		}
	}

	user.setRoom(nullptr);

	sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
}
