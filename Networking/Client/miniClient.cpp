#include "miniClient.h"

namespace Networking
{
	MiniClient::MiniClient()
		: m_socket{}
	{
	}
	MiniClient::~MiniClient()
	{
	}
	void MiniClient::createSocket()
	{
		addrinfo* result = nullptr;
		addrinfo* ptr = nullptr;
		addrinfo hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		int iResult = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
		if (iResult != 0)
		{
			printf("getaddrinfo failed %d\n", iResult);
			WSACleanup();
			return;
		}

		m_socket = INVALID_SOCKET;

		ptr = result;

		m_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (m_socket == INVALID_SOCKET)
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return;
		}
	}
	void MiniClient::connectToServer()
	{
	}
}