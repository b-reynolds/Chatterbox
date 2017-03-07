#include "cmd_enter.h"
#include "string_util.h"
#include <string>

void CmdEnter::Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(!user.has_name())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You must register a username before performing this command.");
		SendData(user, cmd_error.Generate());
		return;
	}

	size_t paramSize = parameters.size();

	if(paramSize == 0)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Invalid parameters specified. (Command: ENTER <Room> [Password])");
		SendData(user, cmd_error.Generate());
		return;
	}

	std::string roomNameL = StringUtil::lower(parameters[0]);

	Room* room = nullptr;
	for(unsigned int i = 0; i < rooms.size(); ++i)
	{
		if (StringUtil::lower(rooms[i].name()) == roomNameL)
		{
			room = &rooms[i];
		}
	}

	if(room == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Room does not exist.");
		SendData(user, cmd_error.Generate());
		return;
	}

	if(room->locked())
	{
		if(paramSize < 2 || parameters[1] != room->password())
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Invalid password.");
			SendData(user, cmd_error.Generate());
			return;
		}
	}

	if(room->full())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Room full.");
		SendData(user, cmd_error.Generate());
		return;		return;
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

	auto cmd_enter_room = CommandPacket("ENTERROOM");
	cmd_enter_room.add_param(user.name());

	std::string packet_enter_room = cmd_enter_room.Generate();

	for (auto & u : room->users())
	{
		SendData(*u, packet_enter_room);
	}

	for (auto & u : users)
	{
		if (u.connected() && u.has_name())
		{
			for (auto & p : packet_rooms)
			{
				SendData(u, p);
			}
		}
	}
}