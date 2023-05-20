#include "RequestHandlerFactory.h"

// C'tor

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : _loginManager(database), _database(database)
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return _loginManager;
}
