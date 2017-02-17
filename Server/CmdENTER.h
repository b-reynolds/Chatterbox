#pragma once
#include "Command.h"

class CmdENTER : public Command
{

public:

	CmdENTER() : Command(CmdType::ENTER) {}

	void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

	~CmdENTER();

};

