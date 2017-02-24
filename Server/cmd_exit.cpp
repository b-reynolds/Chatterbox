#include "cmd_exit.h"
#include <string>

void CmdEXIT::Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(user.room() == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You are not in a room.");
		SendData(user, cmd_error.Generate());
		return;
	}

	auto cmd_exit_room = CommandPacket("EXITROOM");
	cmd_exit_room.add_param(user.name());

	std::string packet_exit_room = cmd_exit_room.Generate();

	for (auto & u : user.room()->users())
	{
		SendData(*u, packet_exit_room);
	}

	user.room()->remove_user(&user);
	user.set_room(nullptr);

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
