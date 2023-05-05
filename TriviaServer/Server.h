#pragma once

#include "Communicator.h"

class Server
{
public:
	/// <summary>
	/// The main method of the server
	/// which activates the communicator between the server and the clients
	/// </summary>
	void run();

private:
	Communicator _communicator;
};
