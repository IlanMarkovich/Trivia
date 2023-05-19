#pragma once

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include <map>

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

#define PORT 7777
#define CODE_SIZE 1
#define LEN_SIZE 4

using std::map;

class Communicator
{
public:
	void startHandleRequests();

private:
	// FIELDS
	SOCKET _serverSocket;
	map<SOCKET, IRequestHandler*> _clients;
	RequestHandlerFactory _handlerFactory;

	// METHODS
	void bindAndListen();
	void handleNewClient(SOCKET client);

	RequestInfo recieveRequest(SOCKET client);
	void sendResponse(SOCKET client, RequestInfo info);
};

