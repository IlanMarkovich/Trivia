#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <map>

#include "IRequestHandler.h"

using std::map;

class Communicator
{
private:
	// FIELDS
	SOCKET _serverSocket;
	map<SOCKET, IRequestHandler*> _clients;

	// METHODS
	void bindAndListen();
	void handleNewClient(SOCKET client);

public:
	void startHandleRequests();
};

