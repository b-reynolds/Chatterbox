#include "Command.h"
#include <algorithm>

void Command::sendMessage(const User& user, const std::string& message) const
{
	send(user.getSocket(), message.c_str(), static_cast<int>(message.length()), 0);
}


/**
 * \brief Converts a string to lower case
 * \param string string to convert
 */
std::string Command::toLower(std::string string) const
{
	transform(string.begin(), string.end(), string.begin(), tolower);
	return string;
}

/**
 * \brief Builds a string by concatenating a vector of strings. Each string is prefixed with a joint.
 * \param strings strings to concatenate
 * \param joint character to use as a joint
 */
std::string Command::buildString(const std::vector<std::string>& strings, const char& joint) const
{
	std::string string;
	for(int i = 0; i < strings.size(); ++i)
	{
		if(i != 0)
		{
			string += joint;
		}
		string += strings[i];
	}
	return string;
}

CommandType Command::getCommandType() const
{
	return commandType;
}
