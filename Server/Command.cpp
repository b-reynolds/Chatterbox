#include "Command.h"
#include <algorithm>
#include <numeric>

void Command::sendMessage(const User& user, const std::string& message) const
{
	send(user.getSocket(), message.c_str(), message.length(), 0);
}

std::string Command::convertToLower(const std::string& string) const
{
	std::string output = string;
	transform(output.begin(), output.end(), output.begin(), tolower);
	return output;
}

std::string Command::getString(const std::vector<std::string>& strings) const
{
	std::string string;
	string = accumulate(strings.begin(), strings.end(), string, BindStrings());
	return string;
}


CommandType Command::getCommandType() const
{
	return commandType;
}
