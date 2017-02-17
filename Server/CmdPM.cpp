#include "CmdPM.h"
#include <numeric>

void CmdPM::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	if(parameters.size() < 2)
	{
		sendMessage(user, statusToString(CmdStatus::ERR_INVALID));
		return;
	}

	std::string recipient = parameters[0];
	parameters.erase(parameters.begin());

	std::string message = buildString(parameters, ' ');

	// £%$%

	for(int i = 0; i < users.size(); ++i)
	{
		if(user.getID() != users[i].getID())
		{
			if(toLower(users[i].getUsername()) == toLower(recipient))
			{
				user.sendMessage(users[i], "(PM) " + user.getUsername() + ": " + message);
				sendMessage(user, statusToString(CmdStatus::SUCCESS));
				printf("\t#%d %s > (%d) %s : %s\n", user.getID(), user.getUsername().c_str(), users[i].getID(), users[i].getUsername().c_str(), message.c_str());
				return;
			}
		}
	}

	sendMessage(user, statusToString(CmdStatus::ERR_NOUSR));
}
