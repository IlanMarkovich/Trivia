#include "RequestHandlerFactory.h"

#include "RoomAdminRequestHandler.h"

// C'tor

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
	: _loginManager(database), _statisticsManager(database), _gameManager(database), _database(database)
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

GameManager& RequestHandlerFactory::getGameManager()
{
	return _gameManager;
}

// METHODS

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(string username)
{
	return new MenuRequestHandler(*this, _loginManager[username]);
}

IRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user, Room& room)
{
	return new RoomMemberRequestHandler(*this, user, room);
}

IRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room& room)
{
	return new RoomAdminRequestHandler(*this, user, room);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(Game& game, Room& room, const LoggedUser& user)
{
	return new GameRequestHandler(*this, game, room, user);
}
