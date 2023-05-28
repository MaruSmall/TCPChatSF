#include "Chat_ClientTCP.h"

int main() {

    Chat_ClientTCP client;

    if (client.createSocket())
    {
        client.connectServer();
    }

    return 0;
}