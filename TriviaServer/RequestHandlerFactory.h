#pragma once

#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager _loginManger;
	IDatabase* _database;

public:
	LoginRequestHandler* createLoginRequestHandler() const;
	LoginManager& getLoginManager() const;
};
