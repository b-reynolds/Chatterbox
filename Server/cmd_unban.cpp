#include "cmd_unban.h"
#include "command_packet.h"
#include "string_util.h"
#include <string>

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdUnban::execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if (!user.has_name())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You must register a username before performing this command.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure required parameters are specified

	size_t paramSize = parameters.size();

	if (paramSize == 0)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Invalid parameters specified. (Command: UNBAN <User>)");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure the user is in a room

	Room* room_user_in = user.room();

	if (room_user_in == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You are not in a room");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure the user owns the room

	if (room_user_in->owner()->id() != user.id())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You do not own this room.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure the specified user exists and is banned

	std::string recipient_name_l = StringUtil::lower(parameters[0]);
	User* recipient = nullptr;

	for (unsigned int i = 0; i < users.size(); ++i)
	{
		if (!users[i].connected() || StringUtil::lower(users[i].name()) != recipient_name_l)
		{
			continue;
		}

		recipient = &users[i];
	}

	if (recipient == nullptr || !room_user_in->banned(*recipient))
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("The specified user does not exist / is not banned.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Unban the user

	auto cmd_banned = CommandPacket("INFO");
	cmd_banned.add_param("You were unbanned from \"" + room_user_in->name() + "\".");

	room_user_in->unban(*recipient);

	send_data(*recipient, cmd_banned.generate());

	auto cmd_success = CommandPacket("INFO");
	cmd_success.add_param("User was unbanned from the room");

	send_data(user, cmd_success.generate());

}
