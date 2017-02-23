#include "cmd_pm.h"

/*
* \brief Execute the command
* \param user calling user
* \param users connected users
* \param rooms server rooms
* \param parameters command parameters
*/
void CmdPM::Execute(User& user, std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Ensure the user has a name

	if (!user.HasName())
	{
		SendData(user, StatusToPacket(Status::kInvalid).Generate());
		return;
	}

	// Ensure required parameters were specified

	if(parameters.size() < 2)
	{
		SendData(user, StatusToPacket(Status::kInvalid).Generate());
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
		SendData(user, StatusToPacket(Status::kNoUsr).Generate());
		return;
	}

	// Ensure message is within the character limit

	std::string message = BuildString(parameters, ' ');
	size_t msgLen = message.length();

	if (msgLen < kMsgLengthMin)
	{
		SendData(user, StatusToString(Status::kShort));
		return;
	}

	if (msgLen > kMsgLengthMax)
	{
		SendData(user, StatusToString(Status::kLong));
		return;
	}

	// Send the message

	auto packet_pm = CommandPacket("PM");
	packet_pm.add_params(std::vector<std::string>({ user.name(), message }));
	
	user.SendData(*recipient, packet_pm.Generate());

	SendData(user, StatusToPacket(Status::kSuccess).Generate());
}
