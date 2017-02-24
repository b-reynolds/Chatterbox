#include "cmd_pm.h"
#include <string>

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdPm::Execute(User& user, std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if (!user.HasName())
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("You must register a username before performing this command.");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure required parameters were specified

	if(parameters.size() < 2)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Invalid parameters specified. (Command: PM <Recipient> <Message>)");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure recipient exists (and is not calling user)

	std::string recipient_name = parameters[0];
	parameters.erase(parameters.begin());

	std::string recipient_name_l = ToLower(recipient_name);

	User* recipient = nullptr;
	for(auto & u : users)
	{
		std::string u_name_l = ToLower(u.name());
		if(u_name_l == recipient_name_l && u_name_l != ToLower(user.name()))
		{
			recipient = &u;
			break;
		}
	}

	if(recipient == nullptr)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("User does not exist.");
		SendData(user, cmd_error.Generate());
		return;
	}

	if(user.IsBlocked(recipient))
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Communication blocked.");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Ensure message is within the character limit

	std::string message = BuildString(parameters, ' ');
	size_t msgLen = message.length();

	if (msgLen < kMsgLengthMin)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Message too short (Min: " + std::to_string(kMsgLengthMin) + ").");
		SendData(user, cmd_error.Generate());
		return;
	}

	if (msgLen > kMsgLengthMax)
	{
		auto cmd_error = CommandPacket("ERROR");
		cmd_error.add_param("Message too long (Max: " + std::to_string(kMsgLengthMax) + ").");
		SendData(user, cmd_error.Generate());
		return;
	}

	// Send the message

	auto packet_pm = CommandPacket("PM");
	packet_pm.add_params(std::vector<std::string>({ user.name(), message }));
	
	user.SendData(*recipient, packet_pm.Generate());
}
