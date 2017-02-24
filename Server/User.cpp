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

int User::id() const
{
	return id_;
}

void User::set_socket(SOCKET socket)
{
	socket_ = socket;
}

SOCKET User::socket() const
{
	return socket_;
}

void User::set_name(const std::string& username)
{
	name_ = username;
}

std::string User::name() const
{
	return name_;
}

void User::set_room(Room* room)
{
	room_ = room;
}

Room* User::room() const
{
	return room_;
}

void User::Block(User* user)
{
	blocked_.push_back(user);
}

void User::Unblock(User* user)
{
	for(unsigned int i = 0; i < blocked_.size(); ++i)
	{
		if(blocked_[i]->name() == user->name())
		{
			blocked_.erase(blocked_.begin() + i);
		}
	}
}

std::vector<User*> User::blocked() const
{
	return blocked_;
}

bool User::IsBlocked(User* user)
{
	for(auto & u : blocked_)
	{
		if(user->name() == u->name())
		{
			return true;
		}
	}

	for(auto & u : user->blocked())
	{
		if(name_ == u->name())
		{
			return true;
		}
	}

	return false;
}

void User::SendData(User& user, const std::string& message)
{
	if (user.Connected() && user.HasName() && !IsBlocked(&user))
	{
		send(user.socket(), message.c_str(), message.length(), 0);
	}
}

void User::SendData(std::vector<User>& users, const std::string& message)
{
	for(auto & user : users)
	{
		if (!IsBlocked(&user))
		{
			SendData(users, message);
		}
	}
}

void User::SendData(Room* room, const std::string& message)
{
	for(auto & user : room->users())
	{
		if (!IsBlocked(user))
		{
			SendData(*user, message);
		}
	}
}

void User::Reset()
{
	if (room_ != nullptr)
	{
		room_->remove_user(this);
	}

	room_ = nullptr;
	name_ = kUsernameNone;

	id_ = kIdNone;

	closesocket(socket_);
	socket_ = INVALID_SOCKET;
}

bool User::Connected() const
{
	return id_ != kIdNone && socket_ != INVALID_SOCKET;
}

bool User::HasName() const
{
	return name_ != kUsernameNone;
}

