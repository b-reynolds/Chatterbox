#include "CmdMKROOM.h"
#include "Room.h"

void CmdMKROOM::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if(!user.hasUsername())
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	// Ensure room name is specified

	size_t paramSize = parameters.size();

	if(paramSize == 0)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	// Ensure room name is within the character limit

	std::string roomName = parameters[0];
	int roomNameLength = roomName.length();

	if (roomNameLength < ROOM_NAME_LENGTH_MIN)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_SHORT));
		return;
	}

	if (roomNameLength > ROOM_NAME_LENGTH_MAX)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_LONG));
		return;
	}

	// Ensure room name contains only alphanumeric or hyphon characters

	for(int i = 0; i < roomNameLength; ++i)
	{
		if(!isalpha(roomName[i]) && roomName[i] != '-')
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_ILLEGAL));
			return;
		}
	}

	std::string roomNameL = toLower(roomName);
	for(int i = 0; i < rooms.size(); ++i)
	{
		// Ensure the user does not currently own a room
		if(rooms[i].getOwner()->getID() == user.getID()) // TODO: ID isn't enough, as ppl can share ID
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
			return;
		}
		// Ensure the room name is unique
		if(toLower(rooms[i].getName()) == roomNameL)
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
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
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
			return;
		}
		// Ensure the capacity is within the set limits
		int capacity = stoi(strCapacity);
		if(capacity < ROOM_SIZE_MIN)
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_SHORT));
			return;
		}
		if (capacity > ROOM_SIZE_MAX)
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_LONG));
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
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_SHORT));
			return;
		}
		if (passLen > ROOM_PASSWORD_LENGTH_MAX)
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_LONG));
			return;
		}
		room.setPassword(pass);
		room.setLocked(true);
	}

	rooms.push_back(room);

	for(auto & usr : users)
	{
		sendMessage(usr, "NROOM:" + room.getName());
	}

	sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
}
