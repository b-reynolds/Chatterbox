#include "command_packet.h"

/**
 * \brief Creates a new command packet
 * \param command command type
 */
CommandPacket::CommandPacket(const std::string command)
{
	command_ = command;
}

/**
 * \brief Adds a parameter to the command
 * \param parameter parameter to add
 */
void CommandPacket::add_param(const std::string parameter)
{
	parameters_.push_back(parameter);
}

/**
 * \brief Adds each string in the vector as a parameter to the command
 * \param parameters parameters to add
 */
void CommandPacket::add_params(const std::vector<std::string> parameters)
{
	for(auto & parameter : parameters)
	{
		add_param(parameter);
	}
}

/**
 * \brief Generates the command packet in the following format $Command:Parameter:Parameter
 */
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
