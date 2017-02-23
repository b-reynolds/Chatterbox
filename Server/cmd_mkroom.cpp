#include "cmd_mkroom.h"
#include "Room.h"
#include <string>

void CmdMKROOM::Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if(!user.HasName())
	{
		SendData(user, StatusToPacket(Status::kInvalid).Generate());
		return;
	}

	// Ensure room name is specified

	unsigned int paramSize = parameters.size();

	if(paramSize == 0)
	{
		SendData(user, StatusToPacket(Status::kInvalid).Generate());
		return;
	}

	// Ensure room name is within the character limit

	std::string roomName = parameters[0];
	unsigned int roomNameLength = roomName.length();

	if (roomNameLength < kRoomNameLengthMin)
	{
		SendData(user, StatusToPacket(Status::kShort).Generate());
		return;
	}

	if (roomNameLength > kRoomNameLengthMax)
	{
		SendData(user, StatusToPacket(Status::kLong).Generate());
		return;
	}

	// Ensure room name contains only alphanumeric or hyphon characters

	for(unsigned int i = 0; i < roomNameLength; ++i)
	{
		if(!isalpha(roomName[i]) && roomName[i] != '-')
		{
			SendData(user, StatusToPacket(Status::kIllegal).Generate());
			return;
		}
	}

	std::string roomNameL = ToLower(roomName);
	for(unsigned int i = 0; i < rooms.size(); ++i)
	{
		// Ensure the user does not currently own a room

		if(rooms[i].owner()->name() == user.name()) // TODO: Pass room ownership on disconnects etc
		{
			SendData(user, StatusToPacket(Status::kInvalid).Generate());
			return;
		}
		// Ensure the room name is unique

		if(ToLower(rooms[i].name()) == roomNameL)
		{
			SendData(user, StatusToPacket(Status::kInvalid).Generate());
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
			SendData(user, StatusToPacket(Status::kInvalid).Generate());
			return;
		}

		// Ensure the capacity is within the set limits

		unsigned int capacity = stoi(strCapacity);
		if(capacity < kRoomSizeMin)
		{
			SendData(user, StatusToPacket(Status::kShort).Generate());
			return;
		}
		if (capacity > kRoomSizeMax)
		{
			SendData(user, StatusToPacket(Status::kLong).Generate());
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
			SendData(user, StatusToString(Status::kShort));
			return;
		}
		if (passLen > kRoomPassLengthMax)
		{
			SendData(user, StatusToString(Status::kLong));
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

	SendData(user, StatusToString(Status::kSuccess));
}
