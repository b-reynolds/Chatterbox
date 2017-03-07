#include "cmd_unblock.h"
#include "string_util.h"

void CmdUnblock::Execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
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
		cmd_error.add_param("Invalid parameters specified. (Command: UNBLOCK <User>)");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure user exists (and is not calling user)

	std::string name_to_unblock = parameters[0];
	parameters.erase(parameters.begin());

	std::string name_to_unblock_l = StringUtil::lower(name_to_unblock);

	User* user_to_unblock = nullptr;
	for (auto & u : users)
	{
		std::string u_name_l = StringUtil::lower(u.name());
		if (u_name_l == name_to_unblock_l && u_name_l != StringUtil::lower(user.name()))
		{
			user_to_unblock = &u;
			break;
		}
	}

	if (user_to_unblock == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("User does not exist.");
		SendData(user, cmd_error.Generate());
		return;
	}

	if (!user.blocked(user_to_unblock))
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("User is not blocked");
		SendData(user, cmd_error.Generate());
	}

	user.unblock(user_to_unblock);
	auto cmd_info = CommandPacket("INFO");
	cmd_info.add_param("User unblocked.");
	SendData(user, cmd_info.Generate());

}
