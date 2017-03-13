#include "string_util.h"
#include <sstream>
#include <algorithm>

/**
* \brief Builds a string by concatenating a vector of strings. Each string is prefixed with a joint.
* \param strings strings to concatenate
* \param joint character to use as a joint
*/
std::string StringUtil::build(const std::vector<std::string>& strings, const char& joint)
{
	std::string string;
	for (unsigned int i = 0; i < strings.size(); ++i)
	{
		if (i != 0)
		{
			string += joint;
		}
		string += strings[i];
	}
	return string;
}

std::vector<std::string> StringUtil::split(const std::string& string, const char& delimiter)
{
	std::vector<std::string> parts;
	std::stringstream ss(string);
	std::string current;

	while (getline(ss, current, delimiter))
	{
		parts.push_back(current);
	}

	return parts;
}

std::string StringUtil::purge(const std::string& string, const char& character)
{
	std::string output = string;
	output.erase(remove(output.begin(), output.end(), character), output.end());
	return output;
}

std::string StringUtil::purge(const std::string& string, const std::vector<char>& characters)
{
	std::string output = string;
	for(auto & character : characters)
	{
		output.erase(remove(output.begin(), output.end(), character), output.end());
	}
	return output;
}

std::string StringUtil::upper(const std::string& string)
{
	std::string output;
	for(auto & character : string)
	{
		output += toupper(character);
	}
	return output;
}

std::string StringUtil::lower(const std::string& string)
{
	std::string output;
	for (auto & character : string)
	{
		output += tolower(character);
	}
	return output;
}
