#include "cmd_message.h"
#include <iostream>
#include <string>

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdMessage::Execute(User& user, std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if(!user.HasName())
	{
		SendData(user, StatusToPacket(Status::kInvalid).GeneratePacket());
		return;
	}

	// Ensure message is within the character limit

	std::string msg = BuildString(parameters, ' ');
	unsigned int msgLen = msg.size();
	
	if(msgLen < kMsgLengthMin)
	{
		SendData(user, StatusToPacket(Status::kShort).GeneratePacket());
		return;
	}

	if(msgLen > kMsgLengthMax)
	{
		SendData(user, StatusToPacket(Status::kLong).GeneratePacket());
		return;
	}

	// Send the message

	auto cmd_msg = CommandPacket("MSG");
	cmd_msg.AddParameter(user.get_name());
	cmd_msg.AddParameter(msg);

	std::string packet_msg = cmd_msg.GeneratePacket();

	Room* user_room = user.get_room();

	if(user_room == nullptr)
	{
		for(auto & u : users)
		{
			user.SendData(u, packet_msg);
		}
		std::cout << "User #" << std::to_string(user.get_id()) << " (" << user.get_name() << ") : " << msg << std::endl;
	}
	else
	{
		user.SendData(user_room, packet_msg);
		std::cout << "User #" << std::to_string(user.get_id()) << " (" << user.get_name() << ") > " << user_room->getName() << " : " << msg << std::endl;
	}

	SendData(user, StatusToPacket(Status::kSuccess).GeneratePacket());
}
