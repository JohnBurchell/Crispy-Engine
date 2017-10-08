#ifndef _MINI_CLIENT_H
#define _MINI_CLIENT_H
#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

// Sockets
#include "..\Networking\socket.h"
#include "..\Networking\ListenSocket.h"

// Client stuff
constexpr const char* DEFAULT_PORT = "27015";
constexpr int DEFAULT_BUFLEN = 512;

namespace Networking
{

	class MiniClient
	{
	public:
		MiniClient();
		~MiniClient();
		
		void createSocket();
		void connectToServer();
		void sendData();
		void receiveData();
		void disconnect();

		SOCKET m_socket;
	};
} // namespace Networking
#endif // _MINI_CLIENT_H
