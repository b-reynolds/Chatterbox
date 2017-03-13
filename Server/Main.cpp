﻿#include <iostream>
#include <vector>
#include <thread>
#include <WinSock2.h>
#include <sstream>
#include "timer.h"
#include "string_util.h"
#include "user.h"
#include "room.h"
#include "commands.h"

const unsigned int kBufferLength = 1024;

const unsigned int kPortMin = 0;
const unsigned int kPortMax = 65535;
const unsigned int kPortDefault = 47861;

const unsigned long kThreadSleepTime = 100;
const unsigned int kTimeoutPeriod = 1800;

const unsigned int kCapacityMin = 0;
const unsigned int kCapacityMax = 100;
const unsigned int kCapacityDefault = 50;

void send_data(SOCKET socket, const std::string& data)
{
	send(socket, data.c_str(), data.length(), 0);
}

void send_data(User& user, const std::string& data)
{
	send(user.socket(), data.c_str(), data.length(), 0);
}

void disconnect_user(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::thread &thread)
{
	std::cout << "User #" + std::to_string(user.id()) + " (" + user.name() + ") disconnected." << std::endl;

	auto cmd_disconnect = CommandPacket("DISCONNECT");
	cmd_disconnect.add_param(user.name());

	int user_id = user.id();

	for (auto & usr : users)
	{
		if (usr.id() != user_id)
		{
			send_data(usr, cmd_disconnect.Generate());
		}
	}

	Room* users_room = user.room();

	if(users_room != nullptr)
	{
		if(users_room->owner()->name() != user.name())
		{
			users_room->remove_user(&user);
		}
		else
		{
			CommandPacket cmd_room_deleted("INFO");
			cmd_room_deleted.add_param("You were removed from the room (Room owner disconnected).");
			std::string packet_room_deleted = cmd_room_deleted.Generate();

			std::string room_name = users_room->name();

			for (unsigned int i = 0; i < rooms.size(); ++i)
			{
				if (rooms[i].name() != room_name)
				{
					continue;
				}

				auto room_users = rooms[i].users();

				for (unsigned int j = 0; j < room_users.size(); ++j)
				{
					send_data(*room_users[j], packet_room_deleted);
					users_room->remove_user(room_users[j]);
				}

				rooms.erase(rooms.begin() + i);

				break;
			}
		}

		// Update the room list of all users

		std::vector<std::string> packet_rooms;
		for(unsigned int i = 0; i < rooms.size(); ++i)
		{
			auto cmd_room = CommandPacket("ROOM");
			cmd_room.add_param(rooms[i].name());
			cmd_room.add_param(std::to_string(rooms[i].users().size()));
			cmd_room.add_param(std::to_string(rooms[i].capacity()));
			cmd_room.add_param(rooms[i].locked() ? "yes" : "no");
			packet_rooms.push_back(cmd_room.Generate());
		}

		if(packet_rooms.empty())
		{
			auto cmd_clear_rooms = CommandPacket("CLEARROOMS");
			packet_rooms.push_back(cmd_clear_rooms.Generate());
		}

		for(unsigned int i = 0; i < users.size(); ++i)
		{
			if(users[i].connected())
			{
				for(unsigned int j = 0; j < packet_rooms.size(); ++j)
				{
					send_data(users[i], packet_rooms[j]);
				}
			}
		}
	}
	
	user.reset();
	thread.detach();
}

int process_user(User &user, std::vector<User> &users, std::vector<Room> &rooms, std::vector<Command*> &commands, std::thread &thread)
{
	Timer timeout(kTimeoutPeriod);
	CmdMessage cmd_message;

	auto cmd_users = CommandPacket("USERS");

	for (auto & u : users)
	{
		if (u.has_name())
		{
			cmd_users.add_param(u.name());
		}
	}

	send_data(user, cmd_users.Generate());

	std::string packet_users = cmd_users.Generate();

	for (auto & r : rooms)
	{
		auto cmd_room = CommandPacket("ROOM");
		cmd_room.add_param(r.name());
		cmd_room.add_param(std::to_string(r.users().size()));
		cmd_room.add_param(std::to_string(r.capacity()));
		cmd_room.add_param(r.locked() ? "yes" : "no");
		send_data(user, cmd_room.Generate());
	}
	
	auto cmd_info = CommandPacket("INFO");
	cmd_info.add_param("Please register a username using the UNAME command (e.g UNAME john)");
	send_data(user, cmd_info.Generate());

	while (true)
	{
		char recv_buffer[kBufferLength] = { 0 };
		int result = recv(user.socket(), recv_buffer, kBufferLength, 0);

		if(timeout.expired() || result == NULL || result == INVALID_SOCKET && WSAGetLastError() != WSAEWOULDBLOCK)
		{
			disconnect_user(user, users, rooms, thread);
			break;
		}

		std::string input = StringUtil::purge(std::string(recv_buffer), std::vector<char>('\n', '\r'));

		if(input.empty())
		{
			continue;
		}

		std::vector<std::string> parameters = StringUtil::split(input, ' ');

		Type command = Command::string_to_type(StringUtil::upper(parameters[0]));

		bool valid_command = false;
		for(auto & c : commands)
		{
			if(command == c->type())
			{
				parameters.erase(parameters.begin());
				c->execute(user, users, rooms, parameters);
				valid_command = true;
			}
		}

		if(!valid_command)
		{
			cmd_message.execute(user, users, rooms, parameters);
		}

		timeout.Reset();

		Sleep(kThreadSleepTime);
	}

	return 0;
}

int main()
{
	std::cout << "========================================================================" << std::endl;
	std::cout << "  00000                                                                 " << std::endl;
	std::cout << "  1     1 1    1   11   11111 11111 111111 11111  11111   1111  1    1 " << std::endl;
	std::cout << "  0       0    0  0  0    0     0   0      0    0 0    0 0    0  0  0  " << std::endl;
	std::cout << "  1       111111 1    1   1     1   11111  1    1 11111  1    1   11   " << std::endl;
	std::cout << "  0       0    0 000000   0     0   0      00000  0    0 0    0   00   " << std::endl;
	std::cout << "  1     1 1    1 1    1   1     1   1      1   1  1    1 1    1  1  1  " << std::endl;
	std::cout << "   00000  0    0 0    0   0     0   000000 0    0 00000   0000  0    0 " << std::endl;
	std::cout << "========================================================================" << std::endl;

	int port = kPortDefault;
	std::string input;

	std::cout << " [!] Enter port number to listen on: ";
		
	getline(std::cin, input);
	std::stringstream string_stream(input);
	
	if(!(string_stream >> port) || port < kPortMin || port > kPortMax)
	{
		std::cout << " [x] Invalid port specified, reverting to default." << std::endl;
		port = kPortDefault;
	}

	unsigned int capacity = kCapacityDefault;

	std::cout << " [!] Enter server capacity: ";

	getline(std::cin, input);
	string_stream = std::stringstream(input);

	if (!(string_stream >> capacity) || capacity < kCapacityMin || capacity > kCapacityMax)
	{
		std::cout << " [x] Invalid capacity specified, reverting to default." << std::endl;
		capacity = kCapacityDefault;
	}

	WORD w_version_requested = MAKEWORD(2, 2);
	WSADATA wsa_data;

	std::cout << " [*] Initializing Winsock... ";
	if(WSAStartup(w_version_requested, &wsa_data) != NULL)
	{
		std::cout << "Failed to initialize Winsock: " << WSAGetLastError() << std::endl;
		WSACleanup();
		getchar();
		return 0;
	}
	std::cout << "OK." << std::endl;

	std::cout << " [*] Creating socket... ";
	SOCKET client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_socket == INVALID_SOCKET)
	{
		std::cout << "Error: Failed to create socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		getchar();
		return 0;
	}
	std::cout << "OK." << std::endl;
		
	// TODO: Experiment with blocking/non-blocking sockets...
	unsigned long mode = 1;
	ioctlsocket(client_socket, FIONBIO, &mode);

	struct sockaddr_in socketAddress, client;
	int client_size = sizeof(client);

	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = ADDR_ANY;
	socketAddress.sin_port = htons(port);

	std::cout << " [*] Binding socket... ";
	if(bind(client_socket, reinterpret_cast<struct sockaddr*>(&socketAddress), sizeof(socketAddress)) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind socket: " << WSAGetLastError() << std::endl;
		closesocket(client_socket);
		WSACleanup();
		getchar();
		return 0;
	}
	std::cout << "OK." << std::endl;

	std::cout << " [*] Listening... ";
	if(listen(client_socket, 256) == SOCKET_ERROR)
	{
		std::cout << "Failed to start listening: " << WSAGetLastError() << std::endl;
		closesocket(client_socket);
		WSACleanup();
		getchar();
		return 0;
	}
	std::cout << "OK (Port: " + std::to_string(port) + ")." << std::endl;	
	std::cout << " [*] Server running... Press ESC to shutdown" << std::endl;
	std::cout << "========================================================================" << std::endl;

	std::vector<User> users(capacity);
	for(unsigned int i = 0; i < capacity; ++i)
	{
		users.push_back(User());
	}

	std::thread threads[kCapacityMax];

	CmdUname cmd_uname;
	CmdPm cmd_pm;
	CmdMkRoom cmd_mkroom;
	CmdEnter cmd_enter;
	CmdExit cmd_exit;
	CmdBlock cmd_block;
	CmdUnblock cmd_unblock;

	std::vector<Command*> commands{ &cmd_uname, &cmd_pm, &cmd_mkroom, &cmd_enter, &cmd_exit, &cmd_block, &cmd_unblock };

	std::vector<Room> rooms;

	while(true)
	{
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			for(unsigned int i = 0; i < capacity; ++i)
			{
				if(users[i].connected())
				{
					disconnect_user(users[i], users, rooms, threads[i]);
				}
			}

			WSACleanup();

			break;
		}

		SOCKET clientSock = accept(client_socket, reinterpret_cast<sockaddr*>(&client), &client_size);

		if (clientSock == INVALID_SOCKET)
		{
			continue;
		}

		int temp_id = User::kIdNone;

		for(unsigned int i = 0; i < capacity; ++i)
		{
			if(!users[i].connected() && !users[i].has_name())
			{
				users[i] = User(i, clientSock);
				temp_id = i;
				break;
			}
		}

		if (temp_id == User::kIdNone)
		{
			send_data(client_socket, CommandPacket("FULL").Generate());
			closesocket(clientSock);
			continue;
		}

		std::cout << "User #" << std::to_string(temp_id) << " connected." << std::endl;
	
		threads[temp_id] = std::thread(process_user, std::ref(users[temp_id]), std::ref(users), std::ref(rooms), std::ref(commands), std::ref(threads[temp_id]));
	}

	return 0;
}
