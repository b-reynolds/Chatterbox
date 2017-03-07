#pragma once
#include <vector>

class StringUtil
{
	
public:

	static std::vector<std::string> split(const std::string& string, const char& delimiter);
	static std::string purge(const std::string& string, const char& character);
	static std::string purge(const std::string& string, const std::vector<char>& characters);
	static std::string upper(const std::string& string);
	static std::string lower(const std::string& string);
	
};