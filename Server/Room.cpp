#include "room.h"

const std::string Room::kPasswordNone = "";

Room::Room(const std::string& name, User* owner, const int& capacity)
{
	name_ = name;
	owner_ = owner;
	capacity_ = capacity;
	locked_ = false;
}

void Room::add_user(User* user)
{
	users_.push_back(user);
}

void Room::remove_user(User* user)
{
	for(unsigned int i = 0; i < users_.size(); ++i)
	{
		if(users_[i]->id() == user->id())
		{
			users_[i]->set_room(nullptr);
			users_.erase(users_.begin() + i);
			break;
		}
	}
}

std::vector<User*>& Room::users()
{
	return users_;
}

std::string Room::name() const
{
	return name_;
}

void Room::set_owner(User* owner)
{
	owner_ = owner;
}

User* Room::owner() const
{
	return owner_;
}

void Room::set_capacity(const int& capacity)
{
	capacity_ = capacity;
}

std::string Room::password() const
{
	return password_;
}

void Room::set_password(const std::string& password)
{
	password_ = password;
	locked_ = password == kPasswordNone ? false : true;
}

void Room::unban(User& user)
{
	for(unsigned int i = 0; i < banned_.size(); ++i)
	{
		if (banned_[i]->id() == user.id())
		{
			banned_.erase(banned_.begin() + i);
			return;
		}
	}
}

void Room::ban(User& user)
{
	for(unsigned int i = 0; i < banned_.size(); ++i)
	{
		if(banned_[i]->id() == user.id())
		{
			return;
		}
	}
	banned_.push_back(&user);
}

bool Room::banned(const User& user)
{
	for(unsigned int i = 0; i < banned_.size(); ++i)
	{
		if(banned_[i]->id() == user.id())
		{
			return true;
		}
	}
	return false;
}

unsigned Room::capacity() const
{
	return capacity_;
}

bool Room::full() const
{
	return users_.size() >= capacity_;
}

bool Room::locked() const
{
	return locked_;
}