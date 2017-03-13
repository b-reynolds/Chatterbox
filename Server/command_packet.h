#pragma once
#include <vector>

/*
 * \brief Class that simplifies building command packets in the following format: $Command:Parameter:Parameter$
 */
class CommandPacket
{

 public:

	/* Constructor sets the command type */
	explicit CommandPacket(const std::string command);

	/* Adds a parameter to the command */
	void add_param(const std::string parameter);

	/* Adds each string in the vector as a parameter to the command */
	void add_params(const std::vector<std::string> parameters);

	/* Generates the command packet in the following format: $Command:Parameter:Parameter */
	std::string generate();

 private:

	/* Characters used to wrap command segments */
	const char kCommandWrapper = '$';
	const char kParameterWrapper = '@';

	/* Vector of command parameters */
	std::vector<std::string> parameters_;

	/* The command type */
	std::string command_;

};

