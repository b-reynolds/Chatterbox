#pragma once
#include <string>
#include <WinSock2.h>
#include <vector>

class Room;

class User
{

public:

	static const int ID_NONE = -1;

	User();
	User(const int &id, SOCKET socket);

	void reset();
	bool isConnected() const;

	void setID(const int &id);
	int getID() const;

	void sendMessage(const User &user, const std::string &message) const;
	void sendMessage(const std::vector<User> &users, const std::string &message) const;

	void setUsername(const std::string &username);
	std::string getUsername() const;

	void setRoom(Room* room);
	Room* getRoom() const;

	bool hasUsername() const;

	void setSocket(SOCKET socket);
	SOCKET getSocket() const;

private:

	static constexpr char* USERNAME_NONE = "";

	Room* room;
	SOCKET socket;

	int id;
	std::string username;

};

