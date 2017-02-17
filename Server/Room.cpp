#include "Room.h"

Room::Room(const std::string& name, User* owner, const int& capacity)
{
	this->name = name;
	this->owner = owner;
	this->size = capacity;
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

User* Room::getOwner()
{
	return owner;
}

Room::~Room()
{
}
