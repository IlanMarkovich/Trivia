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
			result = startGame(info);
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
	CloseRoomResponse response = { sendToAllInRoom(LEAVE_ROOM)};
	_handlerFactory.getRoomManager().deleteRoom(_room.getData().id);

	return { JsonResponsePacketSerializer::serializeResponse(response), _handlerFactory.createMenuRequestHandler(_user.getUsername())};
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	Game& game = _handlerFactory.getGameManager().createGame(_room);

	StartGameResponse response = { sendToAllInRoom(START_GAME)};
	return { JsonResponsePacketSerializer::serializeResponse(response), _handlerFactory.createGameRequestHandler(game, _room, _user)};
}

bool RoomAdminRequestHandler::sendToAllInRoom(RequestType id)
{
	try
	{
		// Builds the request info, to send a response later on
		time_t receivalTime;
		time(&receivalTime);
		RequestInfo info = { id, receivalTime, vector<unsigned char>() };

		// Sends the resposne to all the clients which are in this room and not the admin
		Communicator::sendResponseToClients([this](IRequestHandler* handler) {
			if (dynamic_cast<RoomMemberRequestHandler*>(handler) == nullptr)
			{
				return false;
			}

			RoomMemberRequestHandler roomHandler = *(dynamic_cast<RoomMemberRequestHandler*>(handler));
			LoggedUser user = roomHandler.getUser();

			return _room.hasUser(user) && !(user == _user);
			}, info);
	}
	catch (std::exception& e)
	{
		return false;
	}

	return true;
}
