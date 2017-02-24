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
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You must register a username before performing this command.");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure message is within the character limit

	std::string msg = BuildString(parameters, ' ');
	unsigned int msgLen = msg.size();
	
	if(msgLen < kMsgLengthMin)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Message too short (Min: " + std::to_string(kMsgLengthMin) + ").");
		SendData(user, cmd_error.Generate());
		return;
	}

	if(msgLen > kMsgLengthMax)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Message too long (Max: " + std::to_string(kMsgLengthMax) + ").");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Send the message

	auto cmd_msg = CommandPacket("MSG");
	cmd_msg.add_param(user.name());
	cmd_msg.add_param(msg);

	std::string packet_msg = cmd_msg.Generate();

	Room* user_room = user.room();

	if(user_room == nullptr)
	{
		for(auto & u : users)
		{
			if (u.room() == nullptr)
			{
				user.SendData(u, packet_msg);
			}
		}
		std::cout << "User #" << std::to_string(user.id()) << " (" << user.name() << ") : " << msg << std::endl;
	}
	else
	{
		user.SendData(user_room, packet_msg);
		std::cout << "User #" << std::to_string(user.id()) << " (" << user.name() << ") > " << user_room->name() << " : " << msg << std::endl;
	}
}
