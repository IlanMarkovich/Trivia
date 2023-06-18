#pragma once

#include "IDatabase.h"

#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "GameRequestHandler.h"

#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "GameManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
private:
	IDatabase* _database;

	LoginManager _loginManager;
	RoomManager _roomManager;
	StatisticsManager _statisticsManager;
	GameManager _gameManager;

public:
	// C'tor
	RequestHandlerFactory(IDatabase* database);

	// GETTERS
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
	GameManager& getGameManager();

	// METHODS
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(string username);
	IRequestHandler* createRoomMemberRequestHandler(LoggedUser& user, Room& room);
	IRequestHandler* createRoomAdminRequestHandler(LoggedUser& user, Room& room);
	GameRequestHandler* createGameRequestHandler(Game& game, Room& room, const LoggedUser& user);
};
