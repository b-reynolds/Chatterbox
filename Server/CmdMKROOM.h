#pragma once
#include "Command.h"

class CmdMKROOM : public Command
{

public:

	CmdMKROOM() : Command(CmdType::MKROOM) {};

	void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

private:

	const int ROOM_SIZE_MIN = 2;
	const int ROOM_SIZE_MAX = 128;
	const int ROOM_SIZE_DEFAULT = 32;
	const int ROOM_NAME_LENGTH_MIN = 3;
	const int ROOM_NAME_LENGTH_MAX = 24;
	const int ROOM_PASSWORD_LENGTH_MIN = 8;
	const int ROOM_PASSWORD_LENGTH_MAX = 32;

};

