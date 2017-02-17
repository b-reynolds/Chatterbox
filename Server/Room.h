#pragma once
#include "User.h"

class Room
{

public:

	Room(const std::string &name, User* owner, const int &capacity);
 
	void addUser(User* user);
	std::vector<User*>& getUsers();

	std::string getName() const;
	User* getOwner();

	~Room();

private:

	User* owner;
	std::vector<User*> users;

	bool locked;
	std::string password;
	std::string name;
	int size;

};

