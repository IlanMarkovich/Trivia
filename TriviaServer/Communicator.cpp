#include "Communicator.h"

#include <thread>
#include <string>
#include <iostream>

using std::string;

// PUBLIC METHODS

void Communicator::startHandleRequests()
{
	// Create the server TCP socket
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}

	bindAndListen();
}

// PRIVATE METHODS

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}

	// Endless loop which listens for new clients, accepts them, and sends them to the client handler
	while (true)
	{
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		SOCKET clientSocket = accept(_serverSocket, NULL, NULL);

		if (clientSocket == INVALID_SOCKET)
		{
			throw std::exception(__FUNCTION__);
		}

		// Create thread for handling the client
		std::thread clientThread(&Communicator::handleNewClient, this, clientSocket);
		clientThread.detach();
	}
}

void Communicator::handleNewClient(SOCKET client)
{
	string message = "Hello"; // Test message
	int res = send(client, message.c_str(), message.size(), 0);

	if (res == INVALID_SOCKET)
	{
		std::cerr << "Error while sending message to client";
	}

	char* data = new char[message.size() + 1];
	res = recv(client, data, message.size() + 1, 0);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(client);
		std::cerr << s;
	}

	std::cout << "Message got from client: " << data << std::endl;;

	delete[] data;
	closesocket(client);
}
