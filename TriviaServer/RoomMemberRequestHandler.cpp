#include "RoomMemberRequestHandler.h"

// C'tor

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room)
	: _handlerFactory(handlerFactory), _user(user), _room(room)
{
}

// PUBLIC METHODS

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == LEAVE_ROOM || info.id == GET_ROOM_STATE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	return info.id == LEAVE_ROOM ? leaveRoom(info) : getRoomState(info);
}

// PRIVATE METHODS

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	
}
