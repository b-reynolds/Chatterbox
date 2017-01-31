#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <WinSock2.h>
#include "Client.h"
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT 47861
#define DEFAULT_BUFFLEN 512
#define MAX_CLIENTS 5
#define ID_UNSET -1

bool sendData(const SOCKET &clientSock, const std::string &data)
{
	char dataBuffer[DEFAULT_BUFFLEN];
	strcpy_s(dataBuffer, data.c_str()); // TODO: Handle data being too large for dataBuffer
	int iSendResult = send(clientSock, dataBuffer, data.length(), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("Error: failed to send data to client (%d)\n", WSAGetLastError());
		closesocket(clientSock);
		WSACleanup();
		return false;
	}
	return true;
}

int processClient(Client &client, std::vector<Client> &client_array, std::thread &thread)
{
	std::string message = "";

	char recvBuffer[DEFAULT_BUFFLEN];

	while(true)
	{
		memset(recvBuffer, 0, DEFAULT_BUFFLEN);
		int result = recv(client.getSocket(), recvBuffer, DEFAULT_BUFFLEN, 0);

		if(result != SOCKET_ERROR)
		{
			if (strcmp("", recvBuffer) && recvBuffer[0] != '\r' && recvBuffer[0] != '\n')
			{
				for(int i = 0; i < MAX_CLIENTS; i++)
				{
					if(client_array[i].isValid())
					{
						if((client.getID() != i))
						{
							message = "Client #" + std::to_string(client_array[i].getID()) + ": " + std::string(recvBuffer);
							std::cout << message << std::endl;
							result = send(client_array[i].getSocket(), message.c_str(), strlen(message.c_str()), 0);
						}
					}
				}
			}
		}
		else
		{
			message = "Client #" + std::to_string(client.getID()) + " disconnected";
			std::cout << message << std::endl;

			closesocket((client.getSocket()));
			closesocket(client_array[client.getID()].getSocket());
			client_array[client.getID()].setSocket(INVALID_SOCKET);

			for(int i = 0; i < MAX_CLIENTS; i++)
			{
				if(client_array[i].isValid())
				{
					if(client.getID() != i)
					{
						result = send(client_array[i].getSocket(), message.c_str(), strlen(message.c_str()), 0);
					}
				}
			}
			
			thread.detach();
			return 0;
		}
	}
}

void printWSAError(const std::string &message)
{
	printf("Error: %s (%d)\n", message.c_str(), WSAGetLastError());
}

void printInfo(const std::string &message)
{
	printf("[*] %s\n", message.c_str());
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

	int temp_id = ID_UNSET;

	int size = sizeof(client);
	std::string message;

	while(true)
	{
		SOCKET clientSock = accept(sock, reinterpret_cast<sockaddr*>(&client), &size);
		if (clientSock == INVALID_SOCKET) continue;

		temp_id = ID_UNSET;

		for(int i = 0; i < MAX_CLIENTS; ++i)
		{
			if(clients[i].getSocket() == INVALID_SOCKET && temp_id == ID_UNSET)
			{
				clients[i].setSocket(clientSock);
				clients[i].setID(i);
				temp_id = i;
			}
		}

		if(temp_id != ID_UNSET)
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
