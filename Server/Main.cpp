#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <WinSock2.h>
#include "timer.h"
#include "user.h"
#include <algorithm>
#include <sstream>
#include <numeric>
#include "cmd_message.h"
#include "cmd_uname.h"
#include "cmd_pm.h"
#include "Room.h"
#include "cmd_mkroom.h"
#include "cmd_enter"
#include "cmd_exit.h"
#include "command_packet.h"
#pragma comment(lib, "Ws2_32.lib")

const int kPort = 47861;
const int kClientsMax = 25;
const int kBufferLength = 1024;
const int kTimeoutPeriod = 1800;

void SendData(SOCKET socket, const std::string& data)
{
	send(socket, data.c_str(), data.length(), 0);
}

void SendData(User& user, const std::string& data)
{
	send(user.socket(), data.c_str(), data.length(), 0);
}

std::string ToUpper(std::string string)
{
	transform(string.begin(), string.end(), string.begin(), toupper);
	return string;
}

std::string sanitize(std::string string)
{
	string.erase(remove(string.begin(), string.end(), '\n'), string.end());
	string.erase(remove(string.begin(), string.end(), '\r'), string.end());
	return string;
}

std::vector<std::string> split(const std::string& string, char delimiter)
{
	std::vector<std::string> parts;
	std::stringstream ss(string);
	std::string current;

	while (getline(ss, current, delimiter))
	{ 
		parts.push_back(current);
	}

	return parts;
}

void Disconnect(User &user, std::vector<User> &users, std::thread &thread)
{
	std::cout << "User #" + std::to_string(user.id()) + " (" + user.name() + ") disconnected." << std::endl;

	if(user.room() != nullptr)
	{
		user.room()->remove_user(&user);
	}

	auto cmd_disconnect = CommandPacket("DISCONNECT");
	cmd_disconnect.add_param(user.name());

	int user_id = user.id();

	for (auto & u : users)
	{
		if (u.id() != user_id)
		{
			SendData(u, cmd_disconnect.Generate());
		}
	}

	user.Reset();
	thread.detach();
}

int processClient(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<Command*> &commands, std::thread &thread)
{
	Timer timeout(kTimeoutPeriod);
	CmdMessage cmd_message;

	SendData(user, Command::StatusToPacket(Status::kSuccess).Generate());
	
	auto cmd_info = CommandPacket("INFO");
	cmd_info.add_param("Please specify a username using the UNAME command (e.g UNAME john)");
	SendData(user, cmd_info.Generate());

	while (true)
	{
		char recv_buffer[kBufferLength] = { 0 };
		int result = recv(user.socket(), recv_buffer, kBufferLength, 0);

		if(timeout.expired() || result == NULL || result == INVALID_SOCKET && WSAGetLastError() != WSAEWOULDBLOCK)
		{
			Disconnect(user, users, thread);
			break;
		}

		std::string input = sanitize(std::string(recv_buffer));

		if(input.empty())
		{
			continue;
		}

		std::vector<std::string> parameters = split(input, ' ');

		Type command = Command::StringToType(ToUpper(parameters[0]));

		bool valid_command = false;
		for(auto & c : commands)
		{
			if(command == c->type())
			{
				parameters.erase(parameters.begin());
				c->Execute(user, users, rooms, parameters);
				valid_command = true;
			}
		}

		if(!valid_command)
		{
			cmd_message.Execute(user, users, rooms, parameters);
		}

		timeout.Reset();

		Sleep(100);
	}

	return 0;
}

int main()
{
	std::cout << "============================================" << std::endl;
	std::cout << "Chat Server" << std::endl;
	std::cout << "============================================" << std::endl;

	WORD w_version_requested = MAKEWORD(2, 2);
	WSADATA wsa_data;

	std::cout << "Initializing Winsock... ";
	if(WSAStartup(w_version_requested, &wsa_data) != NULL)
	{
		std::cout << "Failed to initialize Winsock: " << WSAGetLastError() << std::endl;
		WSACleanup();
		getchar();
		return 0;
	}
	std::cout << "OK." << std::endl;

	std::cout << "Creating socket... ";
	SOCKET client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_socket == INVALID_SOCKET)
	{
		std::cout << "Error: Failed to create socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		getchar();
		return 0;
	}
	std::cout << "OK." << std::endl;

	unsigned long mode = 1;
	ioctlsocket(client_socket, FIONBIO, &mode);

	struct sockaddr_in socketAddress, client;
	int client_size = sizeof(client);

	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = ADDR_ANY;
	socketAddress.sin_port = htons(kPort);

	std::cout << "Binding socket... ";
	if(bind(client_socket, reinterpret_cast<struct sockaddr*>(&socketAddress), sizeof(socketAddress)) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind socket: " << WSAGetLastError() << std::endl;
		closesocket(client_socket);
		WSACleanup();
		getchar();
		return 0;
	}
	std::cout << "OK." << std::endl;

	std::cout << "Listening... ";
	if(listen(client_socket, 256) == SOCKET_ERROR)
	{
		std::cout << "Failed to start listening: " << WSAGetLastError() << std::endl;
		closesocket(client_socket);
		WSACleanup();
		getchar();
		return 0;
	}
	std::cout << " OK (" + std::to_string(kPort) + ")." << std::endl;
	
	std::cout << "============================================" << std::endl;

	std::vector<User> users(kClientsMax);
	for(int i = 0; i < kClientsMax; ++i)
	{
		users.push_back(User());
	}

	std::thread threads[kClientsMax];


	std::vector<Command*> commands{ new CmdUname(), new CmdPM(), new CmdMKROOM(), new CmdENTER(), new CmdEXIT() };

	std::vector<Room> rooms;

	while(true)
	{
		SOCKET clientSock = accept(client_socket, reinterpret_cast<sockaddr*>(&client), &client_size);

		if (clientSock == INVALID_SOCKET)
		{
			continue;
		}

		int temp_id = User::kIdNone;

		for(int i = 0; i < kClientsMax; ++i)
		{
			if(!users[i].Connected() && !users[i].HasName())
			{
				users[i] = User(i, clientSock);
				temp_id = i;
				break;
			}
		}

		if (temp_id == User::kIdNone)
		{
			SendData(client_socket, CommandPacket("FULL").Generate());
			closesocket(clientSock);
			continue;
		}

		std::cout << "User #" << std::to_string(temp_id) << " connected." << std::endl;
	
		threads[temp_id] = std::thread(processClient, std::ref(users[temp_id]), std::ref(users), std::ref(rooms), std::ref(commands), std::ref(threads[temp_id]));
	}

	for(int i = 0; i < kClientsMax; ++i)
	{
		if(users[i].Connected())
		{
			users[i].Reset();
			threads[i].detach();
		}
	}

	WSACleanup();

	return 0;
}
