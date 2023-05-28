#include "TCPChatServer.h"
#include <arpa/inet.h>

TCPChatServer::~TCPChatServer()
{
    close(_socket_file_descriptor);
}

bool TCPChatServer::createSocket()
{
    _socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (_socket_file_descriptor == -1) {
        std::cout << "Failed to create socket!" << std::endl;
        return false;
    }

    _serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);

    _serveraddress.sin_port = htons(PORT);

    _serveraddress.sin_family = AF_INET;

    _bind_status = bind(_socket_file_descriptor, (struct sockaddr*)&_serveraddress,
        sizeof(_serveraddress));

    if (_bind_status == -1) {
        std::cout << "Socket binding error!" << std::endl;
        return false;;
    }

    return true;
}

void TCPChatServer::connectClient()
{
    _connection_status = listen(_socket_file_descriptor, 5);

    if (_connection_status == -1) {
        std::cout << "The socket cannot accept new connections!" << std::endl;
        exit(1);
    }
    else {
        std::cout << "The server is waiting for a new connection..." << std::endl;
    }

    _length = sizeof(_client);
    _connection = accept(_socket_file_descriptor, (struct sockaddr*)&_client, &_length);

    if (_connection == -1) {
        std::cout << "The server cannot accept data from the client!" << std::endl;
        exit(1);
    }

    std::cout << "Server: received a connection from" << inet_ntoa(_client.sin_addr) << " port " << ntohs(_client.sin_port) << std::endl;
    communication();
}

void TCPChatServer::communication()
{
    while (1) {
        bzero(_message, MESSAGE_LENGTH);

        std::cout << "Server message: ";
        std::cin.getline(_message, MESSAGE_LENGTH);

        ssize_t bytes = write(_connection, _message, sizeof(_message));

        if (bytes >= 0) {
            std::cout << "Data successfully sent to the client!" << std::endl;
        }

        bzero(_message, MESSAGE_LENGTH);
        read(_connection, _message, sizeof(_message));

        if (strncmp("end", _message, 3) == 0) {
            std::cout << "Client logged out" << std::endl;
            std::cout << "Press any key to exit..." << std::endl;
            std::cin.get();
            return;
        }

        std::cout << "Message for client: " << _message << std::endl;
    }
}