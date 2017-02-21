#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <WinSock2.h>
#include "Timer.h"
#include "User.h"
#include <algorithm>
#include <sstream>
#include <numeric>
#include "CmdMESSAGE.h"
#include "CmdUNAME.h"
#include "CmdPM.h"
#include "Room.h"
#include "CmdMKROOM.h"
#include "CmdENTER.h"
#include "CmdEXIT.h"
#pragma comment(lib, "Ws2_32.lib")

const int PORT = 47861;
const int CLIENTS_MAX = 2500;
const int BUFFLEN = 1024;

const int TIMEOUT = 1800;

void disconnectClient(User &user, std::vector<User> &users, std::thread &thread, std::string message)
{
	printf("[x] Client #%d (%s) disconnected (%s)\n", user.getID(), user.getUsername().c_str(), message.c_str());
	
	std::string output = "$DISCONNECT:" + user.getUsername() + "$";

	for (int i = 0; i < CLIENTS_MAX; i++)
	{
		if (users[i].isConnected())
		{
			send(users[i].getSocket(), output.c_str(), output.length(), 0);
		}
	}

	closesocket(user.getSocket());
	users[user.getID()].reset();
	thread.detach();
}

std::string sanitize(std::string string)
{
	string.erase(std::remove(string.begin(), string.end(), '\n'), string.end());
	string.erase(std::remove(string.begin(), string.end(), '\r'), string.end());
	return string;
}

void sendMessage(SOCKET socket, const std::string &message)
{
	send(socket, message.c_str(), message.length(), 0);
}

void sendMessage(const User &user, const std::string &message)
{
	send(user.getSocket(), message.c_str(), message.size(), 0);
}

void sendMessage(const std::vector<User> &users, const std::string &message)
{
	for(int i = 0; i < users.size(); ++i)
	{
		if(users[i].isConnected() && users[i].hasUsername())
		{
			sendMessage(users[i], message);
		}
	}
}

std::vector<std::string> split(const std::string &string, char delimiter)
{
	std::vector<std::string> parts;
	std::stringstream stringStream(string);
	std::string current;

	while (getline(stringStream, current, delimiter))
	{
		parts.push_back(current);
	}

	return parts;
}

int processClient(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<Command*> &commands, std::thread &thread)
{
	Timer timeOut(TIMEOUT);
	while (true)
	{
		char recvBuffer[BUFFLEN] = { 0 };

		std::string input;
		std::string output;

		int error = 0;

		int result = recv(user.getSocket(), recvBuffer, BUFFLEN, 0);

		if (timeOut.hasExpired()) // TODO: Cleanup room stuff 
		{
			disconnectClient(user, users, thread, "timed out");
			return 0;
		}

		if(result == NULL || result == INVALID_SOCKET && (error = WSAGetLastError()) != WSAEWOULDBLOCK)
		{
			disconnectClient(user, users, thread, "Error: " + std::to_string(error));
			break;
		}

		input = sanitize(std::string(recvBuffer));

		if(input.empty())
		{
			continue;
		}

		printf("Raw: %s\n", recvBuffer);

		std::vector<std::string> parameters = split(input, ' ');

		std::string command = parameters[0];
		parameters.erase(parameters.begin());
		transform(command.begin(), command.end(), command.begin(), toupper);

		CmdType cmd = Command::stringToCmdType(command);
		for(int i = 0; i < commands.size(); ++i)
		{
			if(cmd == commands[i]->getCommandType())
			{
				commands[i]->execute(user, users, rooms, parameters);
				timeOut.reset();
			}
		}

		Sleep(100);

	}
}



int main()
{
	system("cls");
	system("color 0E");
	printf("============================================\n");
	printf(" CHAT SERVER\n");
	printf("============================================\n");

	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;

	printf("[*] Initializing Winsock...\n");
	if(WSAStartup(wVersionRequested, &wsaData) != NULL)
	{
		printf("Error: Failed to initialize Winsock (%d)\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	printf("[*] Creating socket...\n");
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock == INVALID_SOCKET)
	{
		printf("[x] Error: Failed to create socket (%d)\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	unsigned long mode = 1;
	ioctlsocket(sock, FIONBIO, &mode);

	struct sockaddr_in socketAddress, client;
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = ADDR_ANY;
	socketAddress.sin_port = htons(PORT);

	printf("[*] Binding socket...\n");
	if(bind(sock, reinterpret_cast<struct sockaddr*>(&socketAddress), sizeof(socketAddress)) == SOCKET_ERROR)
	{
		printf("[x] Error: Failed to bind socket (%d)\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	printf("[*] Listening... (%d)\n", PORT);
	if(listen(sock, 256) == SOCKET_ERROR)
	{
		printf("[x] Failed to start listening (%d)\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 0;
	}
	
	printf("============================================\n");

	std::vector<User> users;
	for(int i = 0; i < CLIENTS_MAX; ++i)
	{
		users.push_back(User());
	}

	std::thread threads[CLIENTS_MAX];

	int size = sizeof(client);
	std::string message;

	std::vector<Command*> commands{ new CmdMESSAGE(), new CmdUNAME(), new CmdPM(), new CmdMKROOM(), new CmdENTER(), new CmdEXIT() };
	std::vector<Room> rooms;

	while(true)
	{
		SOCKET clientSock = accept(sock, reinterpret_cast<sockaddr*>(&client), &size);

		if (clientSock == INVALID_SOCKET)
		{
			continue;
		}

		int temp_id = User::ID_NONE;

		for(int i = 0; i < CLIENTS_MAX; ++i)
		{
			if(!users[i].isConnected())
			{
				users[i] = User(i, clientSock);
				temp_id = i;
				break;
			}
		}

		if(temp_id != User::ID_NONE)
		{
			printf("[*] User #%d has connected\n", users[temp_id].getID());
			sendMessage(clientSock, Command::cmdStatusToString(CmdStatus::SUCCESS));
			threads[temp_id] = std::thread(processClient, std::ref(users[temp_id]), std::ref(users), std::ref(rooms), std::ref(commands), std::ref(threads[temp_id]));
		}
		else
		{
			message = "Server Full";
			send(clientSock, message.c_str(), strlen(message.c_str()), 0);
			closesocket(clientSock);
		}
	}

	for(int i = 0; i < CLIENTS_MAX; ++i)
	{
		threads[i].detach();
		closesocket(users[i].getSocket());
	}

	WSACleanup();

	return 0;
}
