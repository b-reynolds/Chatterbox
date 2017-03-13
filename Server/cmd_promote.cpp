#include "cmd_promote.h"
#include "command_packet.h"
#include "string_util.h"

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdPromote::execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
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
		cmd_error.add_param("Invalid parameters specified. (Command: PROMOTE <User>)");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure the user owns a room

	if(user.room() == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You do not own a room.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure the recipient exists

	std::string recipient_name = parameters[0];
	std::string recipient_name_l = StringUtil::lower(recipient_name);

	User* recipient = nullptr;
	for (auto & u : users)
	{
		std::string u_name_l = StringUtil::lower(u.name());
		if (u_name_l == recipient_name_l && u_name_l != StringUtil::lower(user.name()))
		{
			recipient = &u;
			break;
		}
	}

	if (recipient == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("User does not exist.");
		send_data(user, cmd_error.generate());
		return;
	}

	if (user.blocked(recipient))
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Communication blocked.");
		send_data(user, cmd_error.generate());
		return;
	}

	for(unsigned int i = 0; i < rooms.size(); ++i)
	{
		if(rooms[i].owner()->id() == recipient->id())
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("That user already owns a room.");
			send_data(user, cmd_error.generate());
			return;
		}
	}

	// Hand over room ownership

	user.room()->set_owner(recipient);

	// Alert the calling user and recipient of the transfer

	auto cmd_new_owner = CommandPacket("INFO");
	cmd_new_owner.add_param("You have been promoted to the owner of \"" + user.room()->name() + "\"");

	send_data(*recipient, cmd_new_owner.generate());

	auto cmd_old_owner = CommandPacket("INFO");
	cmd_old_owner.add_param("You passed ownership of \"" + user.room()->name() + "\" to " + recipient->name());

	send_data(user, cmd_old_owner.generate());

}
