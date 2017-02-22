#include "CmdPM.h"
#include <numeric>

void CmdPM::Execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	if(parameters.size() < 2)
	{
		SendData(user, StatusToString(Status::kInvalid));
		return;
	}

	std::string recipient = parameters[0];
	parameters.erase(parameters.begin());

	std::string message = BuildString(parameters, ' ');
	size_t msgLen = message.length();

	if (msgLen < MESSAGE_LENGTH_MIN)
	{
		SendData(user, StatusToString(Status::kShort));
		return;
	}

	if (msgLen > MESSAGE_LENGTH_MAX)
	{
		SendData(user, StatusToString(Status::kLong));
		return;
	}
	
	std::string recipientL = ToLower(recipient);
	for(auto & otherUser : users)
	{
		if(otherUser.get_id() == user.get_id())
		{
			continue;
		}

		if(ToLower(otherUser.get_name()) == recipientL)
		{
			user.SendData(otherUser, "PM:" + user.get_name() + ":" + message);
			SendData(user, StatusToString(Status::kSuccess));
			printf("\t#%d %s > #%d %s : %s\n", user.get_id(), user.get_name().c_str(), otherUser.get_id(), otherUser.get_name().c_str(), message.c_str());
			return;
		}
	}

	SendData(user, StatusToString(Status::kNoUsr));
}
