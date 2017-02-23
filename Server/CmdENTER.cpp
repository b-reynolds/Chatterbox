#include "CmdENTER.h"
#include <string>

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
		if (ToLower(rooms[i].name()) == roomNameL)
		{
			room = &rooms[i];
		}
	}

	if(room == nullptr)
	{
		SendData(user, StatusToString(Status::kExists));
		return;
	}

	if(room->locked())
	{
		if(paramSize < 2 || parameters[1] != room->password())
		{
			SendData(user, StatusToString(Status::kBadPass));
			return;
		}
	}

	if(room->full())
	{
		SendData(user, StatusToString(Status::kFull));
		return;
	}

	if(user.room() != nullptr)
	{
		user.room()->remove_user(&user);
	}

	room->add_user(&user);
	user.set_room(room);

	std::vector<std::string> packet_rooms;
	for (auto & r : rooms)
	{
		auto cmd_room = CommandPacket("ROOM");
		cmd_room.add_param(r.name());
		cmd_room.add_param(std::to_string(r.users().size()));
		cmd_room.add_param(std::to_string(r.capacity()));
		cmd_room.add_param(r.locked() ? "yes" : "no");
		packet_rooms.push_back(cmd_room.Generate());
	}

	for (auto & u : users)
	{
		if (u.Connected() && u.HasName())
		{
			for (auto & p : packet_rooms)
			{
				SendData(u, p);
			}
		}
	}

	SendData(user, StatusToString(Status::kSuccess));
}

CmdENTER::~CmdENTER()
{
}
