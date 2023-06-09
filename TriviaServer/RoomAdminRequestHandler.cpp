#include "RoomAdminRequestHandler.h"

// C'tor

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room)
	: RoomMemberRequestHandler(handlerFactory, user, room)
{
}

// PUBLIC METHODS

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id >= CLOSE_ROOM && info.id <= GET_ROOM_STATE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult result;

	switch (info.id)
	{
		case CLOSE_ROOM:
			result = closeRoom(info);
			break;

		case START_GAME:
			result = closeRoom(info);
			break;

		case GET_ROOM_STATE:
			result = getRoomState(info);
			break;
	}

	return result;
}

// PRIVATE METHODS

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	return RequestResult();
}
