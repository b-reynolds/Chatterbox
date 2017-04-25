#pragma once
#include "catch.hpp"

#include "commands.h"

class DefaultTestScenario
{
	DefaultTestScenario()
	{
		user.set_id(1);
		user.set_name("John");
		user.set_socket(1);
	}

	User user;

};

/* UNAME Command -------------------------------------------------------------- */

TEST_CASE("Username must be specified", "[UNAME]")
{
	std::vector<User> users;
	User user;
	user.set_id(1);
	user.set_socket(1);
	users.push_back(user);

	std::vector<Room> rooms = { Room("Test Room", nullptr, 32) };
	std::vector<std::string> parameters;

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(user, users, rooms, parameters) == false);
}

TEST_CASE("Username must be more than 2 characters long", "[UNAME]")
{
	std::vector<User> users;
	User user;
	user.set_id(1);
	user.set_socket(1);
	users.push_back(user);

	std::vector<Room> rooms = { Room("Test Room", nullptr, 32) };
	std::vector<std::string> parameters = { "jo" };

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(user, users, rooms, parameters) == false);
}

TEST_CASE("Username must be less than 13 characters long", "[UNAME]")
{
	std::vector<User> users;
	User user;
	user.set_id(1);
	user.set_socket(1);
	users.push_back(user);

	std::vector<Room> rooms = { Room("Test Room", nullptr, 32) };
	std::vector<std::string> parameters = { "johnsmith1994" };

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(user, users, rooms, parameters) == false);
}

TEST_CASE("Username must unique", "[UNAME]")
{
	std::vector<User> users;

	User existingUser;
	existingUser.set_id(1);
	existingUser.set_socket(1);
	existingUser.set_name("John");
	users.push_back(existingUser);

	User user;
	user.set_socket(2);
	users.push_back(user);

	std::vector<Room> rooms = { Room("Test Room", nullptr, 32) };
	std::vector<std::string> parameters = { "John" };

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(user, users, rooms, parameters) == false);
}

TEST_CASE("Username must be alphanumeric", "[UNAME]")
{
	std::vector<User> users;
	User user;
	user.set_id(1);
	user.set_socket(1);
	users.push_back(user);

	std::vector<Room> rooms = { Room("Test Room", nullptr, 32) };
	std::vector<std::string> parameters = { "j0hnsm!th" };

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(user, users, rooms, parameters) == false);
}

/* ---------------------------------------------------------------------------- */

/* MESSAGE Command -------------------------------------------------------------- */

TEST_CASE("Message must not be empty", "[MESSAGE]")
{
	std::vector<User> users;
	User user;
	user.set_name("John");
	user.set_id(1);
	user.set_socket(1);
	users.push_back(user);

	std::vector<Room> rooms = { Room("Test Room", nullptr, 32) };
	std::vector<std::string> parameters = { "" };

	CmdMessage cmdMessage;
	REQUIRE(cmdMessage.execute(user, users, rooms, parameters) == false);
}

TEST_CASE("Message must not be more than 128 characters", "[MESSAGE]")
{
	std::vector<User> users;
	User user;
	user.set_name("John");
	user.set_id(1);
	user.set_socket(1);
	users.push_back(user);

	std::vector<Room> rooms = { Room("Test Room", nullptr, 32) };
	std::vector<std::string> parameters = { "GVPqNX78ZaiKbE6oEuAGeohBI4ah49VgA4Xhi8Mvq8WAfNOfvrpPR5se0wp3rXQoUwm0DDf1lX7RSN5cRVTBtZEoWeDukkWMnAfXvzZ3h65PyX8ZFbrSOT0gJ53wjK93a" };

	CmdMessage cmdMessage;
	REQUIRE(cmdMessage.execute(user, users, rooms, parameters) == false);
}

/* ---------------------------------------------------------------------------- */

/* ROOM Command -------------------------------------------------------------- */

TEST_CASE("Users are added to rooms", "[ROOM]")
{
	Room room("Test Room", nullptr, 32);

	REQUIRE(room.users().size() == 0);

	User user;
	user.set_id(1);
	user.set_socket(1);
	user.set_name("John");

	//REQUIRE((room.users().size() == 1 && room.users()[0] == );
}

/* ---------------------------------------------------------------------------- */

TEST_CASE_METHOD(DefaultTestScenario, "")
{

}