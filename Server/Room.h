#pragma once
#include "User.h"

class Room
{

public:

	Room(const std::string &name, User* owner, const int &capacity);
 
	void addUser(User* user);
	void removeUser(User* user);

	std::vector<User*>& getUsers();

	std::string getName() const;
	User* getOwner() const;

	void setCapacity(const int &capacity);

	std::string getPassword() const;
	void setPassword(const std::string &password);

	void setLocked(const bool &state);

	bool isFull() const;
	bool isLocked() const;

	~Room();

private:

	User* owner;
	std::vector<User*> users;

	bool locked;
	std::string password;
	std::string name;
	int capacity;

};

