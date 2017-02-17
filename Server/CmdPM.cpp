#include "CmdPM.h"
#include <numeric>

void CmdPM::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	if(parameters.size() < 2)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	std::string recipient = parameters[0];
	parameters.erase(parameters.begin());

	std::string message = buildString(parameters, ' ');
	size_t msgLen = message.length();

	if (msgLen < MESSAGE_LENGTH_MIN)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_SHORT));
		return;
	}

	if (msgLen > MESSAGE_LENGTH_MAX)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_LONG));
		return;
	}
	
	std::string recipientL = toLower(recipient);
	for(auto & otherUser : users)
	{
		if(otherUser.getID() == user.getID())
		{
			continue;
		}

		if(toLower(otherUser.getUsername()) == recipientL)
		{
			user.sendMessage(otherUser, "(PM) " + user.getUsername() + ": " + message);
			sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
			printf("\t#%d %s > #%d %s : %s\n", user.getID(), user.getUsername().c_str(), otherUser.getID(), otherUser.getUsername().c_str(), message.c_str());
			return;
		}
	}

	sendMessage(user, cmdStatusToString(CmdStatus::ERR_NOUSR));
}
