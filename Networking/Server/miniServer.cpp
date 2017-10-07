#include "miniServer.h"

namespace Networking
{
    MiniServer::MiniServer()
        : m_test_socket()
        , m_server_info()
    {
        setup_server();
    }

    void MiniServer::setup_server()
    {
        m_server_info.m_result = nullptr;
        m_server_info.m_ptr = nullptr;

        ZeroMemory(&m_server_info.m_hints, sizeof(m_server_info.m_hints));
        m_server_info.m_hints.ai_family = AF_INET;
        m_server_info.m_hints.ai_socktype = SOCK_STREAM;
        m_server_info.m_hints.ai_protocol = IPPROTO_TCP;
        m_server_info.m_hints.ai_flags = AI_PASSIVE;

        // Resolve the address and port that the server will be using.

        // TODO - take a in port number or use the default if none is provided.
        int iResult = getaddrinfo(nullptr, DEFAULT_PORT, &m_server_info.m_hints, &m_server_info.m_result);
        if (iResult != 0)
        {
            printf("getaddrinfo failed: %d\n", iResult);
            WSACleanup();
            return;
        }
    }

    void MiniServer::create_socket()
    {
        // Add to list of sockets later?
        m_test_socket.create();
    }

    void MiniServer::bind_socket()
    {
        // Socket binding
        SOCKET sock = m_test_socket.internal_socket();
        int iResult = bind(sock,
            m_server_info.m_result->ai_addr,
            static_cast<int>(m_server_info.m_result->ai_addrlen));
        if (iResult == SOCKET_ERROR)
        {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(m_server_info.m_result);
            m_test_socket.close();
            return;
        }

        // no longer need the addrinfo in result - free this up.
        freeaddrinfo(m_server_info.m_result);
    }

    void MiniServer::accept_connection()
    {
        Socket new_socket;
        new_socket.create(m_server_info.m_result, m_server_info.m_ptr, m_server_info.m_hints);

        SOCKET client_socket = new_socket.internal_socket();

        // attempt to accept a client socket
        client_socket = accept(m_test_socket.internal_socket(), nullptr, nullptr);
        if (client_socket == INVALID_SOCKET)
        {
            printf("accept failed: %d\n", WSAGetLastError());
            m_test_socket.close();
            return;
        }
    }

    void MiniServer::listen_on_socket()
    {
        // Attempt to listen for a connection
        // SOMAXCONN == allow the max number of pending connections
        if (listen(m_test_socket.internal_socket(), SOMAXCONN) == SOCKET_ERROR)
        {
            printf("Listen failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(m_server_info.m_result);
            m_test_socket.close();
            return;
        }
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
