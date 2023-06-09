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
		// Create Requets info
		RequestType id = LEAVE_ROOM;
		time_t receivalTime;
		time(&receivalTime);
		RequestInfo info = { id, receivalTime, vector<unsigned char>() };

		Communicator::sendResponseToClients([this](IRequestHandler* handler) {
			if (dynamic_cast<RoomMemberRequestHandler*>(handler) == nullptr)
			{
				return false;
			}

			RoomMemberRequestHandler roomHandler = *(dynamic_cast<RoomMemberRequestHandler*>(handler));
			return _room.hasUser(roomHandler.getUser());
			}, info);
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
