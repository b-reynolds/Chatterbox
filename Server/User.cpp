#include "user.h"
#include "Room.h"

User::User()
{
	id_ = kIdNone;
	socket_ = INVALID_SOCKET;
	name_ = kUsernameNone;
	room_ = nullptr;
}

User::User(const int& id, SOCKET socket)
{
	id_ = id;
	socket_ = socket;
	name_ = kUsernameNone;
	room_ = nullptr;
}

void User::set_id(const int& id)
{
	id_ = id;
}

int User::get_id() const
{
	return id_;
}

void User::set_socket(SOCKET socket)
{
	socket_ = socket;
}

SOCKET User::get_socket() const
{
	return socket_;
}

void User::set_name(const std::string& username)
{
	name_ = username;
}

std::string User::get_name() const
{
	return name_;
}

void User::set_room(Room* room)
{
	room_ = room;
}

Room* User::get_room() const
{
	return room_;
}

void User::SendData(const User& user, const std::string& message) const
{
	if (user.Connected() && user.HasName())
	{
		send(user.get_socket(), message.c_str(), message.length(), 0);
	}
}

void User::SendData(const std::vector<User>& users, const std::string& message) const
{
	for(auto & user : users)
	{
		SendData(users, message);
	}
}

void User::SendData(Room* room, const std::string& message)
{
	for(auto & user : room->getUsers())
	{
		SendData(*user, message);
	}
}

void User::Reset()
{
	if (room_ != nullptr)
	{
		room_->removeUser(this);
	}

	id_ = kIdNone;
	socket_ = INVALID_SOCKET;
	name_ = kUsernameNone;

	room_ = nullptr;
}

bool User::Connected() const
{
	return id_ != kIdNone && socket_ != INVALID_SOCKET;
}

bool User::HasName() const
{
	return name_ != kUsernameNone;
}

