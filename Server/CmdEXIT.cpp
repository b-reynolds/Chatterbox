#include "CmdEXIT.h"

void CmdEXIT::execute(User& user, const std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(user.getRoom() == nullptr)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	user.getRoom()->removeUser(&user);
	user.setRoom(nullptr);
	
	sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
}
