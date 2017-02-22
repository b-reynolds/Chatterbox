#include "CmdMKROOM.h"
#include "Room.h"
#include <string>

void CmdMKROOM::Execute(User& user, std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if(!user.HasName())
	{
		SendData(user, StatusToString(Status::kInvalid));
		return;
	}

	// Ensure room name is specified

	size_t paramSize = parameters.size();

	if(paramSize == 0)
	{
		SendData(user, StatusToString(Status::kInvalid));
		return;
	}

	// Ensure room name is within the character limit

	std::string roomName = parameters[0];
	int roomNameLength = roomName.length();

	if (roomNameLength < ROOM_NAME_LENGTH_MIN)
	{
		SendData(user, StatusToString(Status::kShort));
		return;
	}

	if (roomNameLength > ROOM_NAME_LENGTH_MAX)
	{
		SendData(user, StatusToString(Status::kLong));
		return;
	}

	// Ensure room name contains only alphanumeric or hyphon characters

	for(int i = 0; i < roomNameLength; ++i)
	{
		if(!isalpha(roomName[i]) && roomName[i] != '-')
		{
			SendData(user, StatusToString(Status::kIllegal));
			return;
		}
	}

	std::string roomNameL = ToLower(roomName);
	for(int i = 0; i < rooms.size(); ++i)
	{
		// Ensure the user does not currently own a room
		if(rooms[i].getOwner()->get_id() == user.get_id()) // TODO: ID isn't enough, as ppl can share ID
		{
			SendData(user, StatusToString(Status::kInvalid));
			return;
		}
		// Ensure the room name is unique
		if(ToLower(rooms[i].getName()) == roomNameL)
		{
			SendData(user, StatusToString(Status::kInvalid));
			return;
		}
	}

	Room room = Room(roomName, &user, ROOM_SIZE_DEFAULT);

	// optional capacity parameter
	if(paramSize >= 2)
	{
		// Ensure the given parameter is an integer
		std::string strCapacity = parameters[1];
		if(strCapacity.find_first_not_of("0123456789") != std::string::npos)
		{
			SendData(user, StatusToString(Status::kInvalid));
			return;
		}
		// Ensure the capacity is within the set limits
		int capacity = stoi(strCapacity);
		if(capacity < ROOM_SIZE_MIN)
		{
			SendData(user, StatusToString(Status::kShort));
			return;
		}
		if (capacity > ROOM_SIZE_MAX)
		{
			SendData(user, StatusToString(Status::kLong));
			return;
		}
		room.setCapacity(capacity);
	}

	// optional password parameter
	if(paramSize >= 3)
	{
		// ensure password is within the character limit
		std::string pass = parameters[2];
		size_t passLen = pass.length();

		if(passLen < ROOM_PASSWORD_LENGTH_MIN)
		{
			SendData(user, StatusToString(Status::kShort));
			return;
		}
		if (passLen > ROOM_PASSWORD_LENGTH_MAX)
		{
			SendData(user, StatusToString(Status::kLong));
			return;
		}
		room.setPassword(pass);
		room.setLocked(true);
	}

	rooms.push_back(room);

	for(auto & usr : users)
	{
		SendData(usr, "NROOM:" + room.getName());
	}

	SendData(user, StatusToString(Status::kSuccess));
}
