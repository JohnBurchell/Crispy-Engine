#include "miniServer.h"

int main()
{
    Networking::MiniServer server;
    server.create_socket();
    server.bind_socket();
    server.listen_on_socket();
    server.accept_connection();
    server.run();
    return 0;
}