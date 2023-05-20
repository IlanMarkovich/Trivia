#include "MenuRequestHandler.h"

// C'tor

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, RoomManager& roomManager, StatisticsManager& statisticsManager, const LoggedUser& user)
	: _handlerFactory(handlerFactory), _user(user), _roomManager(roomManager), _statisticsManager(statisticsManager)
{
}

// PUBLIC METHODS

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	// This condition means that the id of the request is relevant to the menu
	return info.id >= SIGNOUT && info.id <= CREATE_ROOM;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult result;

	switch (info.id)
	{
		case SIGNOUT:
			result = signout(info);
			break;

		case GET_PLAYRES_IN_ROOM:
			result = getPlayersInRoom(info);
			break;

		case GET_PERSONAL_STAT:
			result = getPersonalStat(info);
			break;

		case GET_HIGH_SCORES:
			result = getHighScores(info);
			break;

		case JOIN_ROOM:
			result = joinRoom(info);
			break;

		case CREATE_ROOM:
			result = createRoom(info);
			break;
	}

	return result;
}

// PRIVATE METHODS
