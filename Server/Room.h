#pragma once
#include "user.h"

class Room
{

public:

	Room(const std::string &name, User* owner, const int &capacity);
 
	void add_user(User* user);
	void remove_user(User* user);

	std::vector<User*>& users();

	std::string name() const;

	void set_owner(User* owner);
	User* owner() const;

	void set_capacity(const int &capacity);

	std::string password() const;
	void set_password(const std::string &password);
	
	void unban(User& user);
	void ban(User& user);
	bool banned(const User& user);

	unsigned int capacity() const;

	bool full() const;
	bool locked() const;

private:

	static const std::string kPasswordNone;

	User* owner_;

	std::vector<User*> users_;
	std::vector<User*> banned_;

	bool locked_;
	std::string password_;
	std::string name_;
	unsigned int capacity_;

};

