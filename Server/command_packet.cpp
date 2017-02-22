#include "command_packet.h"

CommandPacket::CommandPacket(const std::string command)
{
	command_ = command;
}

void CommandPacket::AddParameter(const std::string parameter)
{
	parameters_.push_back(parameter);
}

void CommandPacket::AddParameters(const std::vector<std::string> parameters)
{
	for(auto & parameter : parameters)
	{
		AddParameter(parameter);
	}
}

std::string CommandPacket::GeneratePacket()
{
	std::string packet = kCommandWrapper + command_;
	for(auto & parameter : parameters_)
	{
		packet += kParameterWrapper + parameter;
	}
	packet += kCommandWrapper;
	return packet;
}
