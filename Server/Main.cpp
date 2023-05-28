#include "TCPChatServer.h"

int main() {

    TCPChatServer server;
    if (server.createSocket())
    {
        server.connectClient();
    }

    return 0;
}
