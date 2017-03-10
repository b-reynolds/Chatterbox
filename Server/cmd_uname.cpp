#include "cmd_uname.h"
#include "command_packet.h"
#include "string_util.h"
#include <iostream>
#include <string>

/*
 * \brief Execute the command
 * \param user calling user
 * \param users connected users
 * \param rooms server rooms
 * \param parameters command parameters
 */
void CmdUname::Execute(User& user, std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure required parameters were specified

	if(parameters.size() == 0)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Invalid parameters specified. (Command: UNAME <Name>)");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure name is within character limit

	std::string name = parameters[0];
	unsigned int nameLen = name.length();

	if (nameLen < kNameLengthMin)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Username too short (Min " + std::to_string(kNameLengthMin) + ").");
		SendData(user, cmd_error.Generate());
		return;
	}

	if (nameLen > kNameLengthMax)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Username too long (Max " + std::to_string(kNameLengthMax) + ").");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure name consists of alphanumeric characters

	for (unsigned int i = 0; i < nameLen; ++i)
	{
		if (!isalnum(static_cast<unsigned char>(name[i])))
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Username contains illegal characters.");
			SendData(user, cmd_error.Generate());
			return;
		}
	}

	// Ensure the name is unique

	std::string nameL = StringUtil::lower(name);
	for(auto & usr : users)
	{
		if(usr.connected() && StringUtil::lower(usr.name()) == nameL)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("A user with that name already exists.");
			SendData(user, cmd_error.Generate());
			return;
		}
	}

	// Inform users of the name change / user joining

	if(user.has_name())
	{
		auto cmd_change = CommandPacket("CHANGE");
		cmd_change.add_params(std::vector<std::string>({user.name(), name}));
		std::string packet_change = cmd_change.Generate();

		Room* user_room = user.room();

		for(auto & u : users)
		{
			user.send_data(u, packet_change);
		}

		std::cout << "User #" << std::to_string(user.id()) << " changed their name from " << user.name() << " to " << name << std::endl;
	}
	else
	{
		auto cmd_connect = CommandPacket("CONNECT");
		cmd_connect.add_param(name);
		std::string packet_connect = cmd_connect.Generate();

		auto cmd_users = CommandPacket("USERS");
		cmd_users.add_param(name);

		for(auto & u : users)
		{
			if(u.has_name())
			{
				cmd_users.add_param(u.name());
			}
			SendData(u, packet_connect);
		}

		std::string packet_users = cmd_users.Generate();

		std::vector<std::string> packet_rooms;
		for (auto & r : rooms)
		{
			auto cmd_room = CommandPacket("ROOM");
			cmd_room.add_param(r.name());
			cmd_room.add_param(std::to_string(r.users().size()));
			cmd_room.add_param(std::to_string(r.capacity()));
			cmd_room.add_param(r.locked() ? "yes" : "no");
			packet_rooms.push_back(cmd_room.Generate());
		}

		for(auto & u : users)
		{
			if (u.connected() && u.has_name() || u.id() == user.id())
			{
				SendData(u, packet_users);
				for (auto & p : packet_rooms)
				{
					SendData(u, p);
				}
			}	
		}

		std::cout << "User #" << std::to_string(user.id()) << " set their username to " << name << std::endl;
	}

	user.set_name(name);
}

