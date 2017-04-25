#pragma once
#include "command.h"

/*
* \brief Creates a room. The creator of the room is given ownership privileges (EG. MKROOM johns-room johnspassword).
* If a password is specified, the room is locked and requires entry of the password to be accessed.
* Rooms remain active until the owner disconnects. 
*/
class CmdMkRoom : public Command
{

 public:

	CmdMkRoom() : Command(Type::kMkRoom) {};

	bool execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters) override;

 private:

	 /* Accepted room size range */

	const unsigned int kRoomSizeMin = 2;
	const unsigned int kRoomSizeMax = 128;
	const unsigned int kRoomSizeDefault = 32;

	/* Accepted room name length range */

	const unsigned int kRoomNameLengthMin = 3;
	const unsigned int kRoomNameLengthMax = 12;

	/* Accepted password length range */

	const unsigned int kRoomPassLengthMin = 8;
	const unsigned int kRoomPassLengthMax = 32;

};

