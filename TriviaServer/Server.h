#pragma once

#include "Communicator.h"

#include <string>

#define EXIT_COMMAND "EXIT"

using std::string;

class Server
{
public:
	/// <summary>
	/// The main method of the server
	/// which activates the communicator between the server and the clients
	/// </summary>
	void run();

private:
	// FIELD
	Communicator _communicator;

	// METHOD
	void handleCommand(string input);
};
