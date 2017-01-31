#include "Client.h"

Client::Client()
{
	this->id = -1;
	this->socket = INVALID_SOCKET;
}

Client::Client(const int& id, SOCKET socket)
{
	this->id = id;
	this->socket = socket;
}

void Client::setID(const int& id)
{
	this->id = id;
}

int Client::getID() const
{
	return id;
}

void Client::setSocket(SOCKET socket)
{
	this->socket = socket;
}

SOCKET Client::getSocket() const
{
	return socket;
}

bool Client::isValid() const
{
	return socket != INVALID_SOCKET;
}
