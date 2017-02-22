#pragma once
#include "command.h"

class CmdENTER : public Command
{

public:

	CmdENTER() : Command(Type::kEnter) {}

	void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

	~CmdENTER();

};

