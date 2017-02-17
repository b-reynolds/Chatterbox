#include "CmdENTER.h"

void CmdENTER::execute(User& user, const std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(parameters.size() == 0)
	{
		sendMessage(user, statusToString(CmdStatus::ERR_INVALID));
		return;
	}

	std::string roomName = parameters[0];

	Room* room = nullptr;
	for(int i = 0; i < rooms.size(); ++i)
	{
		if (toLower(rooms[i].getName()) == toLower(roomName))
		{
			room = &rooms[i];
		}
	}

	if(room == nullptr)
	{
		sendMessage(user, statusToString(CmdStatus::ERR_EXISTS));
		return;
	}

	user.setRoom(room);
	room->addUser(&user);

	sendMessage(user, statusToString(CmdStatus::SUCCESS));
}

CmdENTER::~CmdENTER()
{
}
