#include "miniServer.h"

namespace Networking
{
    MiniServer::MiniServer()
        : m_test_socket()
    {
    }

    void MiniServer::create_socket()
    {
        addrinfo* result = nullptr;
        addrinfo* ptr = nullptr;
        addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the address and port that the server will be using.
        int iResult = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
        if (iResult != 0)
        {
            printf("getaddrinfo failed: %d\n", iResult);
            WSACleanup();
            return;
        }

        Networking::Socket socket;

        // Socket binding
        iResult = bind(socket.internal_socket(), result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            freeaddrinfo(result);
            socket.close();
            return;
        }

        // no longer need the addrinfo in result - free this up.
        freeaddrinfo(result);

        // Attempt to listen for a connection
        // SOMAXCONN == allow the max number of pending connections
        if (listen(socket.internal_socket(), SOMAXCONN) == SOCKET_ERROR)
        {
            printf("Listen failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            socket.close();
            return;
        }

        SOCKET client_socket = INVALID_SOCKET;

        // attempt to accept a client socket
        client_socket = accept(socket.internal_socket(), nullptr, nullptr);
        if (client_socket == INVALID_SOCKET)
        {
            printf("accept failed: %d\n", WSAGetLastError());
            socket.close();
            return;
        }

        printf("Great success!\n");
    }

    void MiniServer::run()
    {
        // Loop here and listen for the connection, then send some stuffs
        char receive_buffer[DEFAULT_BUFLEN];
        int iResult = 0;
        int iSendResult = 0;
        int receive_buffer_length = DEFAULT_BUFLEN;

        // receive until the connection is closed
        while (iResult > 0)
        {
            iResult = recv(m_test_socket.internal_socket(), receive_buffer, receive_buffer_length, 0);
            if (iResult > 0)
            {
                printf("Bytes received: %d\n", iResult);

                // Echo the buffer back to the sender
                iSendResult = send(m_test_socket.internal_socket(), receive_buffer, iResult, 0);
                if (iSendResult == SOCKET_ERROR)
                {
                    printf("send failed: %d \n", WSAGetLastError());
                    m_test_socket.close();
                    return;
                }

                printf("Bytes send: %d\n", iSendResult);
            }
            else if (iResult == 0)
            {
                printf("Connection closing...\n");
            }
            else
            {
                printf("recv failed: %d\n", WSAGetLastError());
                m_test_socket.close();
                return;
            }
        }

        // close
        iResult = shutdown(m_test_socket.internal_socket(), SD_SEND);
        if (iResult == SOCKET_ERROR)
        {
            printf("shutdown failed: %d\n", WSAGetLastError());
            m_test_socket.close();
            return;
        }

        m_test_socket.close();
        WSACleanup();
    }

    void MiniServer::close()
    {
        
    }
    MiniServer::~MiniServer()
    {

    }
} // namesapce Networking

