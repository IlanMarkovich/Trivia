#pragma once

#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager _loginManager;
	IDatabase* _database;

public:
	// C'tor
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler() const;
	LoginManager& getLoginManager() const;
};
