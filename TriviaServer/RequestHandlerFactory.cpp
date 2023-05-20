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

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return _roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return _statisticsManager;
}

// METHODS

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(*this, _loginManager, _roomManager, _statisticsManager, user.getUsername());
}
