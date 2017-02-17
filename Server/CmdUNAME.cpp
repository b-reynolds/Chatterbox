#include "CmdUNAME.h"

/*
 * \brief Execute the command
 * \param user calling user
 * \param users connected users
 * \param rooms server rooms
 * \param parameters command parameters
 */
void CmdUNAME::execute(User& user, const std::vector<User>& users, std::vector<Room> &rooms, std::vector<std::string>& parameters)
{
	// Check that all required parameters are set

	if(parameters.size() == 0)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_INVALID));
		return;
	}

	// Ensure username is within the character limit

	std::string uname = parameters[0];
	size_t unameLen = uname.length();

	if (unameLen < USERNAME_LENGTH_MIN)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_SHORT));
		return;
	}

	if (unameLen > USERNAME_LENGTH_MAX)
	{
		sendMessage(user, cmdStatusToString(CmdStatus::ERR_LONG));
		return;
	}

	// Ensure username consists of alphanumeric characters

	for (int i = 0; i < unameLen; ++i) // TODO: Check $% chars
	{
		if (!isalnum(static_cast<unsigned char>(uname[i])))
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_ILLEGAL));
			return;
		}
	}

	// Perform case insensitive comparisons with all connected users to ensure the username is unique

	std::string unameL = toLower(uname);
	for(auto & otherUser : users)
	{
		if(otherUser.isConnected() && unameL == toLower(otherUser.getUsername()))
		{
			sendMessage(user, cmdStatusToString(CmdStatus::ERR_EXISTS));
			return;
		}
	}

	// Alert other users of the name change / user joining

	if(user.hasUsername())
	{
		std::string message = user.getUsername() + " changed their name to " + uname + ".";
		if(user.getRoom() == nullptr)
		{
			for(auto & otherUser : users)
			{
				if(otherUser.getRoom() == nullptr)
				{
					user.sendMessage(otherUser, message);
				}
			}
		}
		else
		{
			Room* room = user.getRoom();
			for(auto & otherUser : room->getUsers())
			{
				user.sendMessage(*otherUser, message);
			}
		}
		printf("[*] User #%d changed their username from %s to %s\n", user.getID(), user.getUsername().c_str(), uname.c_str());
	}
	else
	{
		int userID = user.getID();
		for(auto & otherUser : users)
		{
			if(otherUser.getRoom() == nullptr && otherUser.getID() != userID)
			{
				std::string message = uname + " has joined the server.";
				sendMessage(otherUser, message);
			}
		}
		printf("[*] User #%d set their username to %s\n", userID, uname.c_str());
	}

	user.setUsername(uname);
	sendMessage(user, cmdStatusToString(CmdStatus::SUCCESS));
}

