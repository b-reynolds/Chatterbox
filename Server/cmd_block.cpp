#include "cmd_block.h"
#include "string_util.h"

void CmdBlock::Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if (!user.has_name())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You must register a username before performing this command.");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure required parameters were specified

	if (parameters.size() < 1)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Invalid parameters specified. (Command: BLOCK <User>)");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure user exists (and is not calling user)

	std::string name_to_block = parameters[0];
	parameters.erase(parameters.begin());

	std::string name_to_block_l = StringUtil::lower(name_to_block);

	User* user_to_block = nullptr;
	for (auto & u : users)
	{
		std::string u_name_l = StringUtil::lower(u.name());
		if (u_name_l == name_to_block_l)
		{
			if(u_name_l == StringUtil::lower(user.name()))
			{
				auto cmd_error = CommandPacket("ERROR");
				cmd_error.add_param("You cannot block yourself");
				SendData(user, cmd_error.Generate());
				return;
			}
			user_to_block = &u;
			break;
		}
	}

	if(user_to_block == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("User does not exist.");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Block user

	user.block(user_to_block);

	auto cmd_info = CommandPacket("INFO");
	cmd_info.add_param("User blocked.");
	SendData(user, cmd_info.Generate());
}
