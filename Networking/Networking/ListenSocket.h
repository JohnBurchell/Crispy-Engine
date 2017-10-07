#ifndef _LISTEN_SOCKET_H_
#define _LISTEN_SOCKET_H_
#pragma once

#include "socket.h"

namespace Networking
{
    class ListenSocket
    {
        public:
            ListenSocket();
            ~ListenSocket();

        private:

            Socket m_intnernal_socket;
    };
}

#endif _LISTEN_SOCKET_H_
