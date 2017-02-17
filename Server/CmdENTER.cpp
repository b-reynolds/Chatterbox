#include "CmdENTER.h"

void CmdENTER::execute(User& user, const std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(parameters.size() == 0)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
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
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_EXISTS));
		return;
	}

	room->addUser(&user);
	user.setRoom(room);

	sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
}

CmdENTER::~CmdENTER()
{
}
