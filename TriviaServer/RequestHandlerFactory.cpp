#include "RequestHandlerFactory.h"

// C'tor

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : _loginManager(database), _statisticsManager(database), _database(database)
{
}

// GETTERS

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}

// METHODS

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}