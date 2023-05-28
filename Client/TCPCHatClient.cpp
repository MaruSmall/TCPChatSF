#include "TCPCHatClient.h"

TCPChatClient::~TCPChatClient()
{
    close(_socket_file_descriptor);
}

bool TCPChatClient::createSocket()
{
    _socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_file_descriptor == -1) {
        std::cout << "Failed to create socket!" << std::endl;
        return false;
    }

    _serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    _serveraddress.sin_port = htons(PORT);
    _serveraddress.sin_family = AF_INET;

    return true;
}

void TCPChatClient::connectServer()
{
    _connection = connect(_socket_file_descriptor, (struct sockaddr*)&_serveraddress, sizeof(_serveraddress));
    if (_connection == -1) {
        std::cout << "Connection to the server failed!" << std::endl;
        exit(1);
    }
    std::cout << "The connection to the server is fine..." << std::endl;
    communication();
}

void TCPChatClient::communication()
{
    while (1) {

        bzero(_message, sizeof(_message));
        read(_socket_file_descriptor, _message, sizeof(_message));
        std::cout << "Server message: " << _message << std::endl;

        bzero(_message, sizeof(_message));
        std::cout << "Message for client: ";
        std::cin.getline(_message, MESSAGE_LENGTH);
        if ((strncmp(_message, "end", 3)) == 0) {
            write(_socket_file_descriptor, _message, sizeof(_message));
            std::cout << "Client logged out" << std::endl;
            std::cout << "Press any key to exit..." << std::endl;
            std::cin.get();
            return;
        }
        ssize_t bytes = write(_socket_file_descriptor, _message, sizeof(_message));

        if (bytes >= 0) {
            std::cout << "Data successfully sent to the server!" << std::endl;
        }

    }
}