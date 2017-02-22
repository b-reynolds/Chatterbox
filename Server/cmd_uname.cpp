#include "cmd_uname.h"
#include "command_packet.h"

/*
 * \brief Execute the command
 * \param user calling user
 * \param users connected users
 * \param rooms server rooms
 * \param parameters command parameters
 */
void CmdUNAME::Execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Check that all required parameters are set

	if(parameters.size() == 0)
	{
		SendData(user, StatusToPacket(Status::kInvalid).GeneratePacket());
		return;
	}

	// Ensure name is within the character limit

	std::string name = parameters[0];
	size_t nameLen = name.length();

	if (nameLen < kNameLengthMin)
	{
		SendData(user, StatusToPacket(Status::kShort).GeneratePacket());
		return;
	}

	if (nameLen > kNameLengthMax)
	{
		SendData(user, StatusToPacket(Status::kLong).GeneratePacket());
		return;
	}

	// Ensure name consists of alphanumeric characters

	for (int i = 0; i < nameLen; ++i)
	{
		if (!isalnum(static_cast<unsigned char>(name[i])))
		{
			SendData(user, StatusToPacket(Status::kIllegal).GeneratePacket());
			return;
		}
	}

	// Ensure the name is unique

	std::string nameL = ToLower(name);
	for(auto & usr : users)
	{
		if(usr.Connected() && ToLower(usr.get_name()) == nameL)
		{
			SendData(user, StatusToPacket(Status::kExists).GeneratePacket());
			return;
		}
	}

	// Alert other users of the name change / user joining

	if(user.HasName())
	{
		auto cmd_change = CommandPacket("CHANGE");
		cmd_change.AddParameters(std::vector<std::string>({user.get_name(), name}));
		std::string packet_change = cmd_change.GeneratePacket();

		Room* user_room = user.get_room();

		if(user_room == nullptr)
		{
			for(auto & u : users)
			{
				if(u.get_room() == nullptr)
				{
					user.SendData(u, packet_change);
				}
			}
		}
		else
		{
			user.SendData(user_room, packet_change);
		}
		printf("[*] User #%d changed their username from %s to %s\n", user.get_id(), user.get_name().c_str(), name.c_str());
	}
	else
	{
		auto cmd_connect = CommandPacket("CONNECT");
		cmd_connect.AddParameter(name);
		std::string packet_connect = cmd_connect.GeneratePacket();

		auto cmd_users = CommandPacket("USERS");
		cmd_users.AddParameter(name);

		for(auto & u : users)
		{
			if(u.HasName())
			{
				cmd_users.AddParameter(u.get_name());
			}
			SendData(u, packet_connect);
		}

		std::string packet_users = cmd_users.GeneratePacket();

		for(auto & u : users)
		{
			SendData(u, packet_users);
		}

		printf("[*] User #%d set their username to %s\n", user.get_id(), name.c_str());
	}

	user.set_name(name);

	SendData(user, StatusToPacket(Status::kSuccess).GeneratePacket());
}

