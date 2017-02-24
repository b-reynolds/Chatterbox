#pragma once
#include <vector>

class CommandPacket
{

 public:

	explicit CommandPacket(const std::string command);

	void add_param(const std::string parameter);
	void add_params(const std::vector<std::string> parameters);

	std::string Generate();

 private:

	const char kCommandWrapper = '$';
	const char kParameterWrapper = '@';

	std::vector<std::string> parameters_;
	std::string command_;

};

