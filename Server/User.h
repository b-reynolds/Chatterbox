#pragma once
#include <WinSock2.h>
#include <vector>

class Room;

class User
{

 public:

	static const int kIdNone = -1;
	
	User();
	User(const int& id, SOCKET socket);

	void set_id(const int& id);
	int id() const;

	void set_socket(SOCKET socket);
	SOCKET socket() const;

	void set_name(const std::string& name);
	std::string name() const;

	void set_room(Room* room);
	Room* room() const;

	void Block(User* user);
	void Unblock(User* user);

	std::vector<User*> blocked() const;

	bool IsBlocked(User* user);

	void SendData(User& user, const std::string& message);
	void SendData(std::vector<User>& users, const std::string& message);
	void SendData(Room* room, const std::string& message);

	void Reset();
	bool Connected() const;
	bool HasName() const;

 private:

	static constexpr char* kUsernameNone = "";

	int id_;
	SOCKET socket_;
	std::string name_;
	Room* room_;
	std::vector<User*> blocked_;

};

