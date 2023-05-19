#include "Server.h"

#include <thread>
#include <iostream>

#include "WSAInitializer.h"

// PUBLIC METHODS

void Server::run()
{
	WSAInitializer wsaInit;

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
}

// PRIVATE METHODS

void Server::handleCommand(string input)
{

}
