#include "User.h"
#include <ctype.h>
#include <algorithm>

User::User()
{
	id = ID_NONE;
	socket = INVALID_SOCKET;
	username = USERNAME_NONE;
	room = nullptr;
}

User::User(const int& id, SOCKET socket)
{
	this->id = id;
	this->socket = socket;
	username = USERNAME_NONE;
	room = nullptr;
}

void User::reset()
{
	id = ID_NONE;
	socket = INVALID_SOCKET;
	username = USERNAME_NONE;
	room = nullptr;
}

bool User::isConnected() const
{
	return id != ID_NONE && socket != INVALID_SOCKET;
}

void User::setID(const int& id)
{
	this->id = id;
}

int User::getID() const
{
	return id;
}

void User::sendMessage(const User& user, const std::string& message) const
{
	if (user.isConnected() && user.hasUsername() && user.getID() != id)
	{
		send(user.getSocket(), message.c_str(), message.length(), 0);
	}
}

void User::sendMessage(const std::vector<User>& users, const std::string& message) const
{
	int result = 0;
	for(int i = 0; i < users.size(); ++i)
	{
		if(i != id)
		{
			sendMessage(users[i], message);
		}
	}
}

void User::setUsername(const std::string& username)
{
	this->username = username;
}

std::string User::getUsername() const
{
	return username;
}

void User::setRoom(Room* room)
{
	this->room = room;
}

Room* User::getRoom() const
{
	return room;
}

bool User::hasUsername() const
{
	return username != USERNAME_NONE;
}

void User::setSocket(SOCKET socket)
{
	this->socket = socket;
}

SOCKET User::getSocket() const
{
	return socket;
}
