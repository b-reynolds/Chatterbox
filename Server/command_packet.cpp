#include "command_packet.h"

CommandPacket::CommandPacket(const std::string command)
{
	command_ = command;
}

void CommandPacket::add_param(const std::string parameter)
{
	parameters_.push_back(parameter);
}

void CommandPacket::add_params(const std::vector<std::string> parameters)
{
	for(auto & parameter : parameters)
	{
		add_param(parameter);
	}
}

std::string CommandPacket::Generate()
{
	std::string packet = kCommandWrapper + command_;
	for(auto & parameter : parameters_)
	{
		packet += kParameterWrapper + parameter;
	}
	packet += kCommandWrapper;
	return packet;
}
