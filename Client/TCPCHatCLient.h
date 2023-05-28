#pragma once

#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include <arpa/inet.h>

#define MESSAGE_LENGTH 1024 
#define PORT 7777 

struct TCPChatClient
{
	~TCPChatClient();
	bool createSocket();
	void connectServer();
	void communication();
private:
	struct sockaddr_in _serveraddress;
	struct sockaddr_in _client;
	int _socket_file_descriptor;
	int _connection;
	char _message[MESSAGE_LENGTH];
};