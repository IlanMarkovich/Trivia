#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	// FIELDS
	LoggedUser _user;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;
	RequestHandlerFactory& _handlerFactory;

	// METHODS

public:
	// C'tor
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user);

	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
};
