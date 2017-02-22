#pragma once
#include <vector>

class CommandPacket
{

public:

	explicit CommandPacket(const std::string command);

	void AddParameter(const std::string parameter);
	void AddParameters(const std::vector<std::string> parameters);

	std::string GeneratePacket();

private:

	const char kCommandWrapper = '$';
	const char kParameterWrapper = ':';

	std::vector<std::string> parameters_;
	std::string command_;

};

