#include "cmd_message.h"
#include <iostream>
#include <string>
#include "command_packet.h"

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdMessage::execute(User& user, std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if(!user.has_name())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You must register a username before performing this command.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure message is within the character limit

	std::string msg = build_string(parameters, ' ');
	unsigned int msgLen = msg.size();
	
	if(msgLen < kMsgLengthMin)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Message too short (Min: " + std::to_string(kMsgLengthMin) + ").");
		send_data(user, cmd_error.generate());
		return;
	}

	if(msgLen > kMsgLengthMax)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Message too long (Max: " + std::to_string(kMsgLengthMax) + ").");
		send_data(user, cmd_error.generate());
		return;
	}

	// Send the message

	auto cmd_msg = CommandPacket("MSG");
	cmd_msg.add_param(user.name());
	cmd_msg.add_param(msg);

	std::string packet_msg = cmd_msg.generate();

	Room* user_room = user.room();

	if(user_room == nullptr)
	{
		for(auto & u : users)
		{
			if (u.room() == nullptr)
			{
				user.send_data(u, packet_msg);
			}
		}
		std::cout << "User #" << std::to_string(user.id()) << " (" << user.name() << ") : " << msg << std::endl;
	}
	else
	{
		user.send_data(user_room, packet_msg);
		std::cout << "User #" << std::to_string(user.id()) << " (" << user.name() << ") > " << user_room->name() << " : " << msg << std::endl;
	}
}
