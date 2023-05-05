#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <map>

#include "IRequestHandler.h"

#define PORT 7777

using std::map;

class Communicator
{
public:
	void startHandleRequests();

private:
	// FIELDS
	SOCKET _serverSocket;
	map<SOCKET, IRequestHandler*> _clients;

	// METHODS
	void bindAndListen();
	void handleNewClient(SOCKET client);
};

