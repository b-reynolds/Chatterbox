#pragma once
#include "command.h"

class CmdMkRoom : public Command
{

 public:

	CmdMkRoom() : Command(Type::kMkRoom) {};

	void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

 private:

	const unsigned int kRoomSizeMin = 2;
	const unsigned int kRoomSizeMax = 128;
	const unsigned int kRoomSizeDefault = 32;

	const unsigned int kRoomNameLengthMin = 3;
	const unsigned int kRoomNameLengthMax = 12;

	const unsigned int kRoomPassLengthMin = 8;
	const unsigned int kRoomPassLengthMax = 32;

};

