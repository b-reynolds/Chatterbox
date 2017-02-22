#include "CmdENTER.h"

void CmdENTER::Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(!user.HasName())
	{
		SendData(user, StatusToString(Status::kInvalid));
		return;
	}

	size_t paramSize = parameters.size();

	if(paramSize == 0)
	{
		SendData(user, StatusToString(Status::kInvalid));
		return;
	}

	std::string roomNameL = ToLower(parameters[0]);

	Room* room = nullptr;
	for(int i = 0; i < rooms.size(); ++i)
	{
		if (ToLower(rooms[i].getName()) == roomNameL)
		{
			room = &rooms[i];
		}
	}

	if(room == nullptr)
	{
		SendData(user, StatusToString(Status::kExists));
		return;
	}

	if(room->isLocked())
	{
		if(paramSize < 2 || parameters[1] != room->getPassword())
		{
			SendData(user, StatusToString(Status::kBadPass));
			return;
		}
	}

	if(room->isFull())
	{
		SendData(user, StatusToString(Status::kFull));
		return;
	}

	room->addUser(&user);
	user.set_room(room);

	SendData(user, StatusToString(Status::kSuccess));
}

CmdENTER::~CmdENTER()
{
}
