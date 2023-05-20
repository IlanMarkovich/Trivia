#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	// FIELDS
	string _username;
	LoginManager& _loginManager;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;
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
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager, RoomManager& roomManager, StatisticsManager& statisticsManager, string username);

	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
};
