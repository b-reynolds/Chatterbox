#include "CmdMKROOM.h"
#include "Room.h"

void CmdMKROOM::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	if(!user.hasUsername())
	{
		sendMessage(user, statusToString(ERR_INVALID));
		return;
	}

	if(parameters.size() == 0)
	{
		sendMessage(user, statusToString(ERR_INVALID));
		return;
	}

	std::string roomName = parameters[0];
	int roomNameLength = roomName.length();

	if (roomNameLength < ROOM_NAME_LENGTH_MIN)
	{
		sendMessage(user, statusToString(CmdStatus::ERR_SHORT));
		return;
	}

	if (roomNameLength > ROOM_NAME_LENGTH_MAX)
	{
		sendMessage(user, statusToString(CmdStatus::ERR_LONG));
		return;
	}

	for(int i = 0; i < roomNameLength; ++i)
	{
		if(!isalpha(roomName[i]) && roomName[i] != '-')
		{
			sendMessage(user, statusToString(CmdStatus::ERR_ILLEGAL));
			return;
		}
	}

	for(int i = 0; i < rooms.size(); ++i)
	{
		if(rooms[i].getOwner()->getID() == user.getID())
		{
			sendMessage(user, statusToString(CmdStatus::ERR_INVALID));
			return;
		}
		if(toLower(rooms[i].getName()) == toLower(roomName))
		{
			sendMessage(user, statusToString(CmdStatus::ERR_INVALID));
			return;
		}
	}

	rooms.push_back(Room(roomName, &user, ROOM_SIZE_DEFAULT));

	sendMessage(user, statusToString(CmdStatus::SUCCESS));
	
}
