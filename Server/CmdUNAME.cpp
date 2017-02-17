#include "CmdUNAME.h"
#include <algorithm>

void CmdUNAME::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	std::string username = parameters[0];

	int usernameLength = username.length();

	// Check the username is longer than the minimum length
	if (usernameLength < USERNAME_LENGTH_MIN)
	{
		sendMessage(user, statusToString(ERR_SHORT));
		return;
	}

	// Check if the username is shorter than the maximum length
	if (usernameLength > USERNAME_LENGTH_MAX)
	{
		sendMessage(user, statusToString(ERR_LONG));

		return;
	}

	// Check that the username consists of only alphanumeric characters
	for (int i = 0; i < usernameLength; ++i)
	{
		if (!isalnum(username[i]))
		{
			sendMessage(user, statusToString(ERR_ILLEGAL));
			return;
		}
	}

	// Perform case insensitive username comparisons with all connected users to ensure the username is unique

	for (int i = 0; i < users.size(); ++i)
	{
		if (users[i].isConnected() && convertToLower(username) == convertToLower(users[i].getUsername()))
		{
			sendMessage(user, statusToString(ERR_EXISTS));
			return;
		}
	}

	// If the user had a username previously then alert other users of the name change

	if(user.hasUsername())
	{
		std::string message = user.getUsername() + " changed their name to " + username + ".";
		user.sendMessage(users, message);
	}

	user.setUsername(username);

	sendMessage(user, statusToString(SUCCESS));
}

