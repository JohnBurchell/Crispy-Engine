#ifndef _SOCKET_H_
#define _SOCKET_H_
#pragma once

// Networking headers
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// Below apparently tells the linker that the below file is required - static assert?
#pragma comment(lib, "Ws2_32.lib")

namespace Networking
{
    class Socket
    {
        public:
            Socket();
            ~Socket();

            void create();
            void create(addrinfo * result, const addrinfo * ptr, const addrinfo & hints);
            void close();

            const SOCKET& internal_socket() const { return m_internal_socket; }

        private:

            SOCKET m_internal_socket;

    };
} // namespace Networking

#endif // SOCKET_H_