#pragma once

#include "Communicator.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"
#include "RequestHandlerFactory.h"

#include <string>

#define EXIT_COMMAND "EXIT"

using std::string;

class Server
{
public:
	// C'tor
	Server();

	// D'tor
	~Server();

	/// <summary>
	/// The main method of the server
	/// which activates the communicator between the server and the clients
	/// </summary>
	void run();

private:
	// FIELDS
	Communicator _communicator;
	IDatabase* _database;
	RequestHandlerFactory _handlerFactory;

	// METHOD
	void handleCommand(string input);
};
