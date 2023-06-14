#include "RoomMemberRequestHandler.h"

// C'tor

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, Room& room)
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

// GETTERS

LoggedUser RoomMemberRequestHandler::getUser() const
{
	return _user;
}

// PRIVATE METHODS

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	bool success = true;
	IRequestHandler* newHandler = this;

	try
	{
		_room.removeUser(_user);
		newHandler = _handlerFactory.createMenuRequestHandler(_user.getUsername());
	}
	catch (std::exception& e)
	{
		success = false;
	}

	LeaveRoomResponse response = { success };
	return { JsonResponsePacketSerializer::serializeResponse(response), newHandler };
}

// PROTECTED METHODS

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
	RoomData data = _room.getData();
	GetRoomStateResponse response = { true, data.isActive, _room.getAllUsers(), data.numOfQuestionsInGame, data.timePerQuestion };

	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}
