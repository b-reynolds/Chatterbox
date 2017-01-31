#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <WinSock2.h>
#include "Client.h"
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT 47861
#define DEFAULT_BUFFLEN 1024
#define MAX_CLIENTS 5

void printWSAError(const std::string &message)
{
	printf("Error: %s (%d)\n", message.c_str(), WSAGetLastError());
}

void printInfo(const std::string &message)
{
	printf("[*] %s\n", message.c_str());
}

bool isValidMessage(const char* message)
{
	if(message[0] == '\r')
	{
		return false;
	}
	if(message[0] == '\n')
	{
		return false;
	}
	if(strcmp("", message) == false)
	{
		return false;
	}
	return true;
}

void disconnectClient(Client &client, std::vector<Client> &clients, std::thread &thread)
{
	std::string message = "Client #" + std::to_string(client.getID()) + " disconnected";
	printInfo(message);

	closesocket(client.getSocket());
	clients[client.getID()].reset();


	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (clients[i].isValid() && client.getID() != i)
		{
			send(clients[i].getSocket(), message.c_str(), strlen(message.c_str()), 0);
		}
	}

	thread.detach();
}

std::string sanitize(const std::string &input)
{
	std::string output = input;
	if(output[output.size() - 1] == '\n')
	{
		output.erase(output.size() - 1);
	}
	if(output[output.size() - 1] == '\r')
	{
		output.erase(output.size() - 1);
	}
	return output;
}

int processClient(Client &client, std::vector<Client> &clients, std::thread &thread)
{
	std::string message = "";
	char recvBuffer[DEFAULT_BUFFLEN];

	while (true)
	{
		printf("Thread #%d ACTIVE!\n", client.getID());

		memset(recvBuffer, 0, DEFAULT_BUFFLEN);
		int result = recv(client.getSocket(), recvBuffer, DEFAULT_BUFFLEN, 0);

		if (result == NULL || result == INVALID_SOCKET && WSAGetLastError() != WSAEWOULDBLOCK)
		{
			disconnectClient(client, clients, thread);
			return 0;
		}

		if (isValidMessage(recvBuffer))
		{
			std::string username = "Client #" + std::to_string(client.getID()) + ": ";
			message = username + sanitize(std::string(recvBuffer));

			for (int i = 0; i < MAX_CLIENTS; i++)
			{
				if (clients[i].isValid() && client.getID() != i)
				{
					send(clients[i].getSocket(), message.c_str(), strlen(message.c_str()), 0);
				}
			}
		}

		Sleep(100);
	}
}



int main()
{
	system("cls");
	system("color 17");
	printf("============================================\n");
	printf(" CHAT SERVER\n");
	printf("============================================\n");

	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;

	printInfo("Initializing Winsock");
	if(WSAStartup(wVersionRequested, &wsaData) != NULL)
	{
		printWSAError("Failed to initialize Winsock");
		WSACleanup();
		return 0;
	}

	printInfo("Creating Socket");
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock == INVALID_SOCKET)
	{
		printWSAError("Failed to create Socket");
		WSACleanup();
		return 0;
	}

	unsigned long mode = 1;
	ioctlsocket(sock, FIONBIO, &mode);

	struct sockaddr_in socketAddress, client;
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = ADDR_ANY;
	socketAddress.sin_port = htons(DEFAULT_PORT);

	printInfo("Binding socket");
	if(bind(sock, reinterpret_cast<struct sockaddr*>(&socketAddress), sizeof(socketAddress)) == SOCKET_ERROR)
	{
		printWSAError("Failed to bind socket");
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	printInfo("Listening");
	if(listen(sock, 256) == SOCKET_ERROR)
	{
		printWSAError("Failed to start listening");
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	printf("============================================\n");

	std::vector<Client> clients;
	for(int i = 0; i < MAX_CLIENTS; ++i)
	{
		clients.push_back(Client(-1, INVALID_SOCKET));
	}

	std::thread threads[MAX_CLIENTS];

	int temp_id = Client::ID_UNSET;

	int size = sizeof(client);
	std::string message;

	while(true)
	{
		SOCKET clientSock = accept(sock, reinterpret_cast<sockaddr*>(&client), &size);
		if (clientSock == INVALID_SOCKET) continue;

		temp_id = Client::ID_UNSET;

		for(int i = 0; i < MAX_CLIENTS; ++i)
		{
			if(clients[i].getSocket() == INVALID_SOCKET)
			{
				clients[i].setSocket(clientSock);
				clients[i].setID(i);
				temp_id = i;
				break;
			}
		}

		if(temp_id != Client::ID_UNSET)
		{
			printInfo(std::string("Client #") + std::to_string(clients[temp_id].getID()) + " connected.");
			message = "Connected. You are Client #" + std::to_string(clients[temp_id].getID());

			send(clients[temp_id].getSocket(), message.c_str(), strlen(message.c_str()), 0);
			threads[temp_id] = std::thread(processClient, std::ref(clients[temp_id]), std::ref(clients), std::ref(threads[temp_id]));
		}
		else
		{
			message = "Server Full";
			send(clientSock, message.c_str(), strlen(message.c_str()), 0);
		}
	}

	for(int i = 0; i < MAX_CLIENTS; ++i)
	{
		threads[i].detach();
		closesocket(clients[i].getSocket());
	}

	WSACleanup();

	return 0;
}
