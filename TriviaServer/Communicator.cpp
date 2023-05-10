#include "Communicator.h"

#include <thread>
#include <string>
#include <iostream>
#include <ctime>

#include "LoginRequestHandler.h"

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
		SOCKET client = accept(_serverSocket, NULL, NULL);

		if (client == INVALID_SOCKET)
		{
			throw std::exception(__FUNCTION__);
		}

		LoginRequestHandler* loginHandler = new LoginRequestHandler;
		_clients[client] = loginHandler;

		// Create thread for handling the client
		std::thread clientThread(&Communicator::handleNewClient, this, client);
		clientThread.detach();
	}
}

void Communicator::handleNewClient(SOCKET client)
{
	char* recvData = new char[CODE_SIZE];
	int socketResult = recv(client, recvData, CODE_SIZE, 0);

	if (socketResult == INVALID_SOCKET)
	{
		std::cerr << "Client socket error: " << std::to_string(client) << std::endl;
		return;
	}

	// Get time of receival
	time_t receivalTime;
	time(&receivalTime);

	// Get type of request
	int id = (int)recvData[0];

	// Get request content length
	delete[] recvData;
	recvData = new char[LEN_SIZE];
	socketResult = recv(client, recvData, LEN_SIZE, 0);

	if (socketResult == INVALID_SOCKET)
	{
		std::cerr << "Client socket error: " << std::to_string(client) << std::endl;
		return;
	}

	int requestLength = 0;

	for (int i = 0; i < LEN_SIZE; i++)
	{
		requestLength |= static_cast<int>(recvData[i]) << (8 * (LEN_SIZE - 1 - i));
	}

	// Get request content
	delete[] recvData;
	recvData = new char[requestLength];
	socketResult = recv(client, recvData, requestLength, 0);

	if (socketResult == INVALID_SOCKET)
	{
		std::cerr << "Client socket error: " << std::to_string(client) << std::endl;
		return;
	}

	// Convert the buffer, and create the RequestInfo struct
	vector<unsigned char> buffer(recvData, recvData + requestLength);
	RequestInfo info = { (RequestType)id, requestLength, buffer};

	// If the request is relevent, handle the request and send a response
	if (_clients[client]->isRequestRelevant(info))
	{
		RequestResult result = _clients[client]->handleRequest(info);
		_clients[client] = result.newHandler;

		vector<unsigned char> buffer = result.response;
		string message(buffer.begin(), buffer.end());

		socketResult = send(client, message.c_str(), message.size(), 0);

		if (socketResult == INVALID_SOCKET)
		{
			std::cerr << "Failed to send a message to a client!" << std::endl;
		}
	}

	delete[] recvData;
	closesocket(client);
}
