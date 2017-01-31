#pragma once
#include <WinSock2.h>

class Client
{

public:

	static const int ID_UNSET = -1;
	
	Client();
	Client(const int &id, SOCKET socket);

	void setID(const int &id);
	int getID() const;

	void setSocket(SOCKET socket);
	SOCKET getSocket() const;

	SOCKET* getSocketPointer() { return &socket; }

	bool isValid() const;

	void reset();

private:

	int id;
	SOCKET socket;

};

