#include "cmd_exit.h"
#include <string>
#include "command_packet.h"

void CmdExit::execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	// Ensure the user is in a room

	if(user.room() == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You are not in a room.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Alert others users in the room of the user leaving

	auto cmd_leave_room = CommandPacket("INFO");
	cmd_leave_room.add_param(user.name() + " left the room.");
	user.send_data(user.room(), cmd_leave_room.generate());

	// Remove the user from the room

	user.room()->remove_user(&user);
	user.set_room(nullptr);

	// Update room list of all users

	std::vector<std::string> packet_rooms;
	for (auto & r : rooms)
	{
		auto cmd_room = CommandPacket("ROOM");
		cmd_room.add_param(r.name());
		cmd_room.add_param(std::to_string(r.users().size()));
		cmd_room.add_param(std::to_string(r.capacity()));
		cmd_room.add_param(r.locked() ? "yes" : "no");
		packet_rooms.push_back(cmd_room.generate());
	}

	for (auto & u : users)
	{
		if (u.connected())
		{
			for (auto & p : packet_rooms)
			{
				send_data(u, p);
			}
		}
	}
}
