#include "cmd_enter.h"
#include "string_util.h"
#include <string>
#include "command_packet.h"

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdEnter::execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if(!user.has_name())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You must register a username before performing this command.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure required parameters are specified

	size_t paramSize = parameters.size();

	if(paramSize == 0)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Invalid parameters specified. (Command: ENTER <Room> [Password])");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure room exists

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
		send_data(user, cmd_error.generate());
		return;
	}

	// If the room is locked ensure a password was specified

	if(room->locked())
	{
		if(paramSize < 2 || parameters[1] != room->password())
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Invalid password.");
			send_data(user, cmd_error.generate());
			return;
		}
	}

	// Ensure the room is not full

	if(room->full())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Room full.");
		send_data(user, cmd_error.generate());
		return;		return;
	}

	// If the user is already in the room then return

	if(user.room() == room)
	{
		return;
	}

	// If the user is banned alert them and return
	
	if(room->banned(user))
	{
		auto cmd_banned = CommandPacket("ERROR");
		cmd_banned.add_param("You are currently banned from that room.");
		send_data(user, cmd_banned.generate());
		return;
	}

	// If the user is in a different room already, leave that room and alert other users.

	if(user.room() != nullptr)
	{
		auto cmd_leave_room = CommandPacket("INFO");
		cmd_leave_room.add_param(user.name() + " left the room.");
		user.send_data(room, cmd_leave_room.generate());
		user.room()->remove_user(&user);
	}

	// Add the user to the room and alert the room of their entrance 

	room->add_user(&user);
	user.set_room(room);

	auto cmd_enter_room = CommandPacket("INFO");
	cmd_enter_room.add_param(user.name() + " entered the room");

	std::string packet_enter_room = cmd_enter_room.generate();

	for (auto & u : room->users())
	{
		send_data(*u, packet_enter_room);
	}

	// Update the room list of all users

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
