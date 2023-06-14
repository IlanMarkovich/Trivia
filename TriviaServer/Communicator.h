#pragma once

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include <map>
#include <mutex>
#include <functional>

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

#define PORT 7777
#define CODE_SIZE 1
#define LEN_SIZE 4

using std::map;

class Communicator
{
public:
	// C'tor
	Communicator(RequestHandlerFactory& handlerFactory);

	void startHandleRequests();
	static void sendResponseToClients(std::function<bool(IRequestHandler*)> clientCondition, RequestInfo info);

private:
	// FIELDS
	SOCKET _serverSocket;
	RequestHandlerFactory& _handlerFactory;
	static map<SOCKET, IRequestHandler*> _clients;
	static std::mutex _responseMutex;

	// METHODS
	void bindAndListen();
	void handleNewClient(SOCKET client);

	RequestInfo recieveRequest(SOCKET client);
	static void sendResponse(SOCKET client, RequestInfo info, bool serverSend);
};

