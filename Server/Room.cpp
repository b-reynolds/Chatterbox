#include "Room.h"

Room::Room(const std::string& name, User* owner, const int& capacity)
{
	this->name = name;
	this->owner = owner;
	this->capacity = capacity;
	locked = false;
}

void Room::addUser(User* user)
{
	users.push_back(user);
}

void Room::removeUser(User* user)
{
	for(int i = 0; i < users.size(); ++i)
	{
		if(users[i]->getID() == user->getID())
		{
			users.erase(users.begin() + i);
		}
	}
}

std::vector<User*>& Room::getUsers()
{
	return users;
}

std::string Room::getName() const
{
	return name;
}

User* Room::getOwner() const
{
	return owner;
}

void Room::setCapacity(const int& capacity)
{
	this->capacity = capacity;
}

std::string Room::getPassword() const
{
	return password;
}

void Room::setPassword(const std::string& password)
{
	this->password = password;
}

void Room::setLocked(const bool& state)
{
	locked = state;
}

bool Room::isFull() const
{
	return users.size() >= capacity;
}

bool Room::isLocked() const
{
	return locked;
}

Room::~Room()
{
}
