#pragma once
#include "command.h"

/*
 * \brief Sets or change a User’s name (E.g. UNAME johnsmith).
 * Usernames must be alphanumeric and comprised of a minimum of 3 and a maximum of 12 characters.
 * There may only be one instance of any given username connected to the server at any one time.
 */
class CmdUname : public Command
{

 public:

	CmdUname() : Command(Type::kUName) {};

	void Execute(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

 private:

	// Accepted username length range

	const int kNameLengthMin = 3;
	const int kNameLengthMax = 12;

};