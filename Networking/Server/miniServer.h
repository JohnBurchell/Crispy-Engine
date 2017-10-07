#ifndef _MINISERVER_H_
#define _MINISERVER_H_
#pragma once

// Networking headers
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// misc
#include <vector>

// Below apparently tells the linker that the below file is required - static assert?
#pragma comment(lib, "Ws2_32.lib")

// Sockets
#include "..\Networking\socket.h"
#include "..\Networking\ListenSocket.h"

// SERVER STUFF
constexpr const char* DEFAULT_PORT = "27015";
constexpr int DEFAULT_BUFLEN = 512;

namespace Networking
{
    class MiniServer
    {
    public:
        MiniServer();
        ~MiniServer();
        
        // Run this server!
        void run();

        // Handling sockets
        void create_socket();
        void bind_socket();
        void listen_on_socket();
        void accept_connection();

        // Server only
        void close();

        Socket m_test_socket;
    };
}// namespace Networking
#endif // _MINISERVER_H_
