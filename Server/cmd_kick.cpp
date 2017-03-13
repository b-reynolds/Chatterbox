#include "cmd_kick.h"
#include "command_packet.h"
#include <string>
#include "string_util.h"

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdKick::execute(User& user, std::vector<User>& users, std::vector<Room>& rooms, std::vector<std::string>& parameters)
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
		cmd_error.add_param("Invalid parameters specified. (Command: KICK <User> [Message])");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure the user is in a room

	Room* room_user_in = user.room();

	if(room_user_in == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You are not in a room");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure the user owns the room

	if(room_user_in->owner()->id() != user.id())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You do not own this room.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Ensure the specified user is in the room

	std::string recipient_name_l = StringUtil::lower(parameters[0]);
	User* recipient = nullptr;

	auto room_users = room_user_in->users();
	for(unsigned int i = 0; i < room_users.size(); ++i)
	{
		if(StringUtil::lower(room_users[i]->name()) != recipient_name_l)
		{
			continue;
		}

		recipient = room_users[i];
	}

	if(recipient == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("The specified user does not exist / is not in the room.");
		send_data(user, cmd_error.generate());
		return;
	}

	// Check if optional message was specified / and is within character limit

	std::string message = "";

	if (parameters.size() >= 2)
	{
		parameters.erase(parameters.begin());
		message = StringUtil::build(parameters, ' ');

		unsigned int message_length = message.length();

		if (message_length < kMsgLengthMin)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Message name too short (Min: " + std::to_string(kMsgLengthMin) + ").");
			send_data(user, cmd_error.generate());
			return;
		}

		if (message_length > kMsgLengthMax)
		{
			auto cmd_error = CommandPacket("ERROR");
			cmd_error.add_param("Message name too long (Max: " + std::to_string(kMsgLengthMax) + ").");
			send_data(user, cmd_error.generate());
			return;
		}
	}

	// Kick the user

	auto cmd_kicked = CommandPacket("INFO");
	cmd_kicked.add_param("You were kicked from the room" + (!message.empty() ? " \"" + message + "\"" : ""));

	room_user_in->remove_user(recipient);
	recipient->set_room(nullptr);

	send_data(*recipient, cmd_kicked.generate());

	auto cmd_success = CommandPacket("INFO");
	cmd_success.add_param("User was kicked from the room");

	send_data(user, cmd_success.generate());

	// Update the room list of all users

	std::vector<std::string> packet_rooms;
	for (auto & r : rooms)
	{
		auto cmd_room = CommandPacket("ROOM");
		cmd_room.add_param(r.name());
		cmd_room.add_param(std::to_string(r.users().size()));
		cmd_room.add_param(std::to_string(r.capacity()));
		cmd_room.add_param(r.locked() ? "yes" : "no");
		packet_rooms.push_back(cmd_room.generate());
	}

	for(unsigned int i = 0; i < users.size(); ++i)
	{
		if(!users[i].connected())
		{
			continue;
		}

		for(unsigned int j = 0; j < packet_rooms.size(); ++j)
		{
			send_data(users[i], packet_rooms[j]);
		}
	}

}
