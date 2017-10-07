#include "socket.h"

namespace Networking
{
    Socket::Socket()
    {
        // WSADATA -> used specifically in winsocks?
        WSADATA wsaData;
        
        // init the winsock
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

        if (iResult != 0)
        {
            printf("WSAStartup failed: %d\n", iResult);
            return;
        }
    }

    void Socket::create()
    {
        m_internal_socket = socket(PF_INET, SOCK_STREAM, 0);
        if (m_internal_socket == INVALID_SOCKET)
        {
            printf("Error at socket(): %ld\n", WSAGetLastError());
            return;
        }
    }

    void Socket::create(addrinfo* result, const addrinfo* ptr, const addrinfo& hints)
    {
        m_internal_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        if (m_internal_socket == INVALID_SOCKET)
        {
            printf("Error at socket(): %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return;
        }
    }

    void Socket::close()
    {
        closesocket(m_internal_socket);
        WSACleanup();
    }

    Socket::~Socket()
    {
        close();
    }
}
