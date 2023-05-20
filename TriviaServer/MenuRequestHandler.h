#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	// FIELDS
	LoggedUser _user;
	RequestHandlerFactory& _handlerFactory;

	// METHODS
	RequestResult signout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getPersonalStat(RequestInfo info);
	RequestResult getHighScores(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);

public:
	// C'tor
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user);

	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
};
