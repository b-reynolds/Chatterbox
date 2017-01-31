#pragma once
#include <WinSock2.h>

class Client
{

public:

	Client();
	Client(const int &id, SOCKET socket);

	void setID(const int &id);
	int getID() const;

	void setSocket(SOCKET socket);
	SOCKET getSocket() const;

	bool isValid() const;

private:

	int id;
	SOCKET socket;

};

