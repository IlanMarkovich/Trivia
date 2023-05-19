#include "Server.h"

#include <thread>
#include <iostream>

#include "WSAInitializer.h"

// C'tor

Server::Server() : _database(new SqliteDatabase), _handlerFactory(_database), _communicator(_handlerFactory)
{
}

// D'tor

Server::~Server()
{
	delete _database;
}

// PUBLIC METHODS

void Server::run()
{
	WSAInitializer wsaInit;
	_database->open();

	// Starts listening for clients, and connecting them to the server
	std::thread t_connector(&Communicator::startHandleRequests, _communicator);
	t_connector.detach();
	
	string input;

	// Endless loop for getting input from server admin
	do
	{
		std::cout << "Enter command:" << std::endl;
		std::cin >> input;

		handleCommand(input);
	} while (input != EXIT_COMMAND);

	_database->close();
}

// PRIVATE METHODS

void Server::handleCommand(string input)
{

}
