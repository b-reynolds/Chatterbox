#include "cmd_mkroom.h"
#include "Room.h"
#include <string>

void CmdMkRoom::Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if(!user.HasName())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You must register a username before performing this command.");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure room name is specified

	unsigned int paramSize = parameters.size();

	if(paramSize == 0)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Invalid parameters specified. (Command: MKROOM <Name> [Capacity] [Password])");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure room name is within the character limit

	std::string roomName = parameters[0];
	unsigned int roomNameLength = roomName.length();

	if (roomNameLength < kRoomNameLengthMin)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Room name too short (Min: " + std::to_string(kRoomNameLengthMin) + ").");
		SendData(user, cmd_error.Generate());
		return;
	}

	if (roomNameLength > kRoomNameLengthMax)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Room name too long (Max: " + std::to_string(kRoomNameLengthMax) + ").");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure room name contains only alphanumeric or hyphon characters

	for(unsigned int i = 0; i < roomNameLength; ++i)
	{
		if(!isalpha(roomName[i]) && roomName[i] != '-')
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Room name contains illegal characters.");
			SendData(user, cmd_error.Generate());
			return;
		}
	}

	std::string roomNameL = ToLower(roomName);
	for(unsigned int i = 0; i < rooms.size(); ++i)
	{
		// Ensure the user does not currently own a room

		if(rooms[i].owner()->name() == user.name()) // TODO: Pass room ownership on disconnects etc
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("You already own a room.");
			SendData(user, cmd_error.Generate());
			return;
		}
		// Ensure the room name is unique

		if(ToLower(rooms[i].name()) == roomNameL)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Room name already in use.");
			SendData(user, cmd_error.Generate());
			return;
		}
	}

	Room room = Room(roomName, &user, kRoomSizeDefault);

	// Optional capacity parameter

	if(paramSize >= 2)
	{
		// Ensure the given parameter is an integer

		std::string strCapacity = parameters[1];
		if(strCapacity.find_first_not_of("0123456789") != std::string::npos)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Invalid capacity specified.");
			SendData(user, cmd_error.Generate());
			return;
		}

		// Ensure the capacity is within the set limits

		unsigned int capacity = stoi(strCapacity);
		if(capacity < kRoomSizeMin)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Capacity too small (Min: " + std::to_string(kRoomSizeMin) + ").");
			SendData(user, cmd_error.Generate());
			return;
		}
		if (capacity > kRoomSizeMax)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Capacity too large (Max: " + std::to_string(kRoomSizeMax) + ").");
			SendData(user, cmd_error.Generate());
			return;
		}
		room.set_capacity(capacity);
	}

	// optional password parameter

	if(paramSize >= 3)
	{
		// ensure password is within the character limit

		std::string pass = parameters[2];
		unsigned int passLen = pass.length();

		if(passLen < kRoomPassLengthMin)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Password too short (Min: " + std::to_string(kRoomPassLengthMin) + ").");
			SendData(user, cmd_error.Generate());
			return;
		}
		if (passLen > kRoomPassLengthMax)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Password too long (Max: " + std::to_string(kRoomPassLengthMax) + ").");
			SendData(user, cmd_error.Generate());
			return;
		}
		room.set_password(pass);
	}

	// Create the room and notify other users

	rooms.push_back(room);

	std::vector<std::string> packet_rooms;
	for(auto & r : rooms)
	{
		auto cmd_room = CommandPacket("ROOM");
		cmd_room.add_param(r.name());
		cmd_room.add_param(std::to_string(r.users().size()));
		cmd_room.add_param(std::to_string(r.capacity()));
		cmd_room.add_param(r.locked() ? "yes" : "no");
		packet_rooms.push_back(cmd_room.Generate());
	}

	for(auto & u : users)
	{
		if (u.Connected() && u.HasName())
		{
			for (auto & p : packet_rooms)
			{
				SendData(u, p);
			}
		}
	}

	auto cmd_info = CommandPacket("INFO");
	cmd_info.add_param("Room created.");
	SendData(user, cmd_info.Generate());
}
