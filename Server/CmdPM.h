#pragma once
#include "Command.h"

class CmdPM : public Command
{

public:

	CmdPM() : Command(CmdType::PM) {};

	void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

};
