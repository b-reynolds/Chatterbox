#pragma once
#include <vector>

class StringUtil
{
	
public:

	/* Builds a string by concatenating a vector of strings. Each string is prefixed with a joint. */
	static std::string build(const std::vector<std::string>& strings, const char &joint);

	static std::vector<std::string> split(const std::string& string, const char& delimiter);
	static std::string purge(const std::string& string, const char& character);
	static std::string purge(const std::string& string, const std::vector<char>& characters);
	static std::string upper(const std::string& string);
	static std::string lower(const std::string& string);
	
};