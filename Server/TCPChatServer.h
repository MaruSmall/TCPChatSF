#pragma once
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MESSAGE_LENGTH 1024 
#define PORT 7777 

struct TCPChatServer
{
	~TCPChatServer();
	bool createSocket();
	void connectClient();
	void communication();
private:
	struct sockaddr_in _serveraddress;
	struct sockaddr_in _client;
	socklen_t _length;
	int _socket_file_descriptor;
	int _connection; 
	int _bind_status;
	int _connection_status;
	char _message[MESSAGE_LENGTH];
};
