#include "RoomAdminRequestHandler.h"

#include "Communicator.h"

// C'tor

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user, Room& room)
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
	bool success = true;

	try
	{
		LeaveRoomResponse leaveRoom = { true };

		Communicator::sendResponseToClients(JsonResponsePacketSerializer::serializeResponse(leaveRoom), [this](IRequestHandler* handler) {
			// Part of the condition to send to a certain client the leave response, is only if he is in a room state
			if (dynamic_cast<RoomMemberRequestHandler*>(handler) == nullptr)
			{
				return false;
			}

			// The condition is that the client has to be in a room state, and in this room in particular
			RoomMemberRequestHandler roomHandler = *(dynamic_cast<RoomMemberRequestHandler*>(handler));
			return _room.hasUser(roomHandler.getUser());
			});
	}
	catch (std::exception& e)
	{
		success = false;
	}

	CloseRoomResponse response = { success };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	return RequestResult();
}
