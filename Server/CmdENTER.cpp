#include "CmdENTER.h"

void CmdENTER::execute(User& user, const std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(!user.hasUsername())
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	size_t paramSize = parameters.size();

	if(paramSize == 0)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	std::string roomNameL = toLower(parameters[0]);

	Room* room = nullptr;
	for(int i = 0; i < rooms.size(); ++i)
	{
		if (toLower(rooms[i].getName()) == roomNameL)
		{
			room = &rooms[i];
		}
	}

	if(room == nullptr)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_EXISTS));
		return;
	}

	if(room->isLocked())
	{
		if(paramSize < 2 || parameters[1] != room->getPassword())
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_BADPASS));
			return;
		}
	}

	if(room->isFull())
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_FULL));
		return;
	}

	room->addUser(&user);
	user.setRoom(room);

	sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
}

CmdENTER::~CmdENTER()
{
}
