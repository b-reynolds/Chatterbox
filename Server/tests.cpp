#pragma once
#include "catch.hpp"
#include "commands.h"

#define TESTING 0

#ifndef TESTING

/* Test Scenario -------------------------------------------------------------- */

struct DefaultScenario
{

	const std::vector<std::string> cTestUsers = { "John", "Jane", "Adam", "Eve" };

	const int cValidSocket = 1;
	const int cTestRooms = 10;

	std::vector<User> mUsers;
	std::vector<Room> mRooms;
	std::vector<std::string> mParameters;

	User mUser;

	DefaultScenario()
	{
		for (unsigned int i = 0; i < cTestUsers.size(); ++i)
		{
			User testUser;

			testUser.set_id(i);
			testUser.set_name(cTestUsers[i]);
			testUser.set_socket(cValidSocket);

			mUsers.push_back(testUser);
		}

		mUser = mUsers[0];

		for(unsigned int i = 1; i < cTestRooms; ++i)
		{
			mRooms.push_back(Room(std::string("Room ") + std::to_string(i), nullptr, i));
		}
	}

};

/* ---------------------------------------------------------------------------- */

/* UNAME Command -------------------------------------------------------------- */

TEST_CASE_METHOD(DefaultScenario, "[UNAME] Username must be specified", "[UNAME]")
{
	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[UNAME] Username must be more than 2 characters long", "[UNAME]")
{
	mParameters.push_back("ab");

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[UNAME] Username must be less than 13 characters long", "[UNAME]")
{
	mParameters.push_back("abcdefghijklm");

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[UNAME] Username must unique", "[UNAME]")
{
	mParameters.push_back(mUser.name());

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[UNAME] Username must be alphanumeric", "[UNAME]")
{
	mParameters.push_back("j0hn$m!th");

	CmdUname cmdUname;
	REQUIRE(cmdUname.execute(mUser, mUsers, mRooms, mParameters) == false);
}

/* ---------------------------------------------------------------------------- */

/* MESSAGE Command -------------------------------------------------------------- */

TEST_CASE_METHOD(DefaultScenario, "[MESSAGE] Message must not be empty", "[MESSAGE]")
{
	CmdMessage cmdMessage;
	REQUIRE(cmdMessage.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MESSAGE] Message must not be more than 128 characters", "[MESSAGE]")
{
	mParameters.push_back("GVPqNX78ZaiKbE6oEuAGeohBI4ah49VgA4Xhi8Mvq8WAfNOfvrpPR5se0wp3rXQoUwm0DDf1lX7RSN5cRVTBtZEoWeDukkWMnAfXvzZ3h65PyX8ZFbrSOT0gJ53wjK93a");

	CmdMessage cmdMessage;
	REQUIRE(cmdMessage.execute(mUser, mUsers, mRooms, mParameters) == false);
}

/* ---------------------------------------------------------------------------- */

/* MKROOM Command -------------------------------------------------------------- */

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] User must have a name", "[MKROOM]")
{
	mUser.set_name("");

	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] Room name must be specified", "[MKROOM]")
{
	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] must be more than 2 characters long", "[MKROOM]")
{
	mParameters.push_back("ab");

	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] must be less than 13 characters long", "[MKROOM]")
{
	mParameters.push_back("abcdefghijklm");

	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] Room name must be alphanumeric", "[MKROOM]")
{
	mParameters.push_back("@bcd3fg");

	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] Room name must be unique", "[MKROOM]")
{
	mParameters.push_back(mRooms[0].name());

	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] Room capacity must be an integer", "[MKROOM]")
{
	mParameters.push_back("Room X");
	mParameters.push_back("One");

	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] Room capacity must be at least 2", "[MKROOM]")
{
	mParameters.push_back("Room Y");
	mParameters.push_back("1");

	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[MKROOM] Room capacity must be no more than 128", "[MKROOM]")
{
	mParameters.push_back("Room Z");
	mParameters.push_back("129");

	CmdMkRoom cmdMkRoom;
	REQUIRE(cmdMkRoom.execute(mUser, mUsers, mRooms, mParameters) == false);
}

/* ---------------------------------------------------------------------------- */

/* ENTER Command -------------------------------------------------------------- */

TEST_CASE_METHOD(DefaultScenario, "[ENTER] User must have a name", "[ENTER]")
{
	mUser.set_name("");

	CmdEnter cmdEnter;
	REQUIRE(cmdEnter.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[ENTER] Room name must be specified", "[ENTER]")
{
	CmdEnter cmdEnter;
	REQUIRE(cmdEnter.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[ENTER] Room must exist", "[ENTER]")
{
	mParameters.push_back(mRooms[0].name());

	CmdEnter cmdEnter;
	REQUIRE(cmdEnter.execute(mUser, mUsers, mRooms, mParameters) == true);
}

TEST_CASE_METHOD(DefaultScenario, "[ENTER] Room must not be full", "[ENTER]")
{
	mRooms[0].add_user(&mUsers[1]);
	mParameters.push_back(mRooms[0].name());

	CmdEnter cmdEnter;
	REQUIRE(cmdEnter.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[ENTER] User can not already be in the room", "[ENTER]")
{
	mUser.set_room(&mRooms[1]);
	mParameters.push_back(mRooms[1].name());

	CmdEnter cmdEnter;
	REQUIRE(cmdEnter.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[ENTER] User must not be banned from the room", "[ENTER]")
{
	mRooms[0].ban(mUser);
	mParameters.push_back(mRooms[0].name());

	CmdEnter cmdEnter;
	REQUIRE(cmdEnter.execute(mUser, mUsers, mRooms, mParameters) == false);
}

TEST_CASE_METHOD(DefaultScenario, "[ENTER] Password must be specified for locked rooms", "[ENTER]")
{
	Room lockedRoom("Locked Room", nullptr, 32);
	lockedRoom.set_password("password");

	mParameters.push_back("Locked Room");

	CmdEnter cmdEnter;
	REQUIRE(cmdEnter.execute(mUser, mUsers, mRooms, mParameters) == false);
}

/* ---------------------------------------------------------------------------- */

#endif