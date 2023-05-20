#pragma once

#include "IDatabase.h"

#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
private:
	IDatabase* _database;
	LoginManager _loginManager;
	RoomManager _roomManager;
	StatisticsManager _statisticsManager;

public:
	// C'tor
	RequestHandlerFactory(IDatabase* database);

	// GETTERS
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();

	// METHODS
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(string username);
};
