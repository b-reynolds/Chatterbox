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

	void SendData(const User& user, const std::string& message) const;
	void SendData(const std::vector<User>& users, const std::string& message) const;
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

};

