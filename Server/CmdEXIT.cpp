#include "CmdEXIT.h"

void CmdEXIT::Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	if(user.get_room() == nullptr)
	{
		SendData(user, StatusToString(Status::kInvalid));
		return;
	}

	user.get_room()->removeUser(&user);
	user.set_room(nullptr);
	
	SendData(user, StatusToString(Status::kSuccess));
}
