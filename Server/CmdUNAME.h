#pragma once
#include "Command.h"

/*
 * \brief Sets or change a User’s username (E.g. UNAME johnsmith).
 * Usernames must be alphanumeric and comprised of a minimum of 3 and a maximum of 12 characters.
 * There may only be one instance of any given username connected to the server at any one time.
 */
class CmdUNAME : public Command
{

public:

	/* Default Constructor */
	CmdUNAME() : Command(CmdType::UNAME) {};

	/* Execute the command */
	void execute(User &user, const std::vector<User> &users, std::vector<Room> &rooms, std::vector<std::string> &parameters) override;

private:

	/* Accepted username length range */

	const int USERNAME_LENGTH_MIN = 3;
	const int USERNAME_LENGTH_MAX = 12;

};