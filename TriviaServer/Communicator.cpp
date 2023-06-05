#include "Communicator.h"

#include <thread>
#include <string>
#include <iostream>
#include <ctime>

#include "LoginRequestHandler.h"

using std::string;

// C'tor

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : _handlerFactory(handlerFactory)
{
}

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

		// Set the login request handler as the first request handler for the user's requests
		LoginRequestHandler* loginHandler = _handlerFactory.createLoginRequestHandler();
		_clients[client] = loginHandler;

		// Create thread for handling the client
		std::thread clientThread(&Communicator::handleNewClient, this, client);
		clientThread.detach();
	}
}

void Communicator::handleNewClient(SOCKET client)
{
	try
	{
		while(true)
		{
			RequestInfo info = recieveRequest(client);

			if (info.id != ERR)
			{
				sendResponse(client, info);
			}
			else
			{
				throw std::exception("Disconnected because of an error");
			}
		}
	}
	catch (...)
	{
		std::cout << "Client " << client << " disconnected!" << std::endl << "Enter command:" << std::endl;
	}

	delete _clients[client];
	_clients.erase(client);

	closesocket(client);
}

RequestInfo Communicator::recieveRequest(SOCKET client)
{
	char* recvData = new char[CODE_SIZE];
	int socketResult = recv(client, recvData, CODE_SIZE, 0);

	if (socketResult == INVALID_SOCKET)
	{
		std::cerr << "Client socket error: " << std::to_string(client) << std::endl;
		return {ERR, 0, vector<unsigned char>()};
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
		return { ERR, 0, vector<unsigned char>() };
	}

	int requestLength = 0;
	unsigned char lengthBuffer[LEN_SIZE];

	// Convert the data recieved from a char array to an unsigned char array
	for (int i = 0; i < LEN_SIZE; i++)
	{
		lengthBuffer[i] = static_cast<unsigned char>(recvData[i]);
	}

	// Convert requsetLength from bytes to int
	for (int i = 0; i < LEN_SIZE; i++)
	{
		requestLength |= static_cast<int>(lengthBuffer[i]) << (8 * (LEN_SIZE - 1 - i));
	}

	vector<unsigned char> buffer;

	// Get request content, if there is content to get
	if (requestLength > 0)
	{
		delete[] recvData;
		recvData = new char[requestLength];
		socketResult = recv(client, recvData, requestLength, 0);

		if (socketResult == INVALID_SOCKET)
		{
			std::cerr << "Client socket error: " << std::to_string(client) << std::endl;
			return { ERR, 0, vector<unsigned char>() };
		}

		// Convert the buffer, and return the RequestInfo struct
		buffer = vector<unsigned char>(recvData, recvData + requestLength);
		delete[] recvData;
	}

	return { (RequestType)id, receivalTime, buffer };
}

void Communicator::sendResponse(SOCKET client, RequestInfo info)
{
	// If the request is not relevent, don't send a response
	if (!_clients[client]->isRequestRelevant(info))
	{
		return;
	}

	RequestResult result = _clients[client]->handleRequest(info);
	
	if (_clients[client] != result.newHandler)
	{
		delete _clients[client];
		_clients[client] = result.newHandler;
	}

	vector<unsigned char> buffer = result.response;
	string message(buffer.begin(), buffer.end());

	int socketResult = send(client, message.c_str(), message.size(), 0);

	if (socketResult == INVALID_SOCKET)
	{
		std::cerr << "Failed to send a message to a client!" << std::endl;
	}
}
