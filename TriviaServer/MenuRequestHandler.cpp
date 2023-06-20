#include "MenuRequestHandler.h"

// C'tor

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user)
	: _handlerFactory(handlerFactory), _user(user)
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

		case GET_ROOMS:
			result = getRooms(info);
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

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	bool success = true;

	try
	{
		_handlerFactory.getLoginManager().logout(_user.getUsername());
	}
	catch (std::exception& e)
	{
		success = false;
	}

	LogoutResponse response = { success };
	return { JsonResponsePacketSerializer::serializeResponse(response), _handlerFactory.createLoginRequestHandler() };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	GetRoomResponse response = { !_handlerFactory.getRoomManager().getRooms().empty(), _handlerFactory.getRoomManager().getRooms()};
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
	Room room = _handlerFactory.getRoomManager().getRoom(request.roomId);

	GetPlayersInRoomResponse response = { !room.getAllUsers().empty(), room.getAllUsers()};
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::getPersonalStat(RequestInfo info)
{
	vector<string> statistics = _handlerFactory.getStatisticsManager().getUserStatistics(_user.getUsername());

	GetPersonalStatResponse response = { !statistics.empty(), statistics };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::getHighScores(RequestInfo info)
{
	vector<string> highScores = _handlerFactory.getStatisticsManager().getHighScores();

	GetHighScoresResponse response = { !highScores.empty(), highScores };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	JoinRoomRequset request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	bool success = true;
	IRequestHandler* newHandler = this;
	Room* room = nullptr;

	try
	{
		room = &(_handlerFactory.getRoomManager().getRoom(request.roomId));
		room->addUser(_user);

		newHandler = _handlerFactory.createRoomMemberRequestHandler(_user, *room);
	}
	catch (std::exception& e)
	{
		success = false;
	}

	JoinRoomResponse response = {success, room->getData().name};

	return { JsonResponsePacketSerializer::serializeResponse(response), newHandler};
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
	bool success = true;
	IRequestHandler* newHandler = this;

	try
	{
		// If there are no rooms give the id 1, else set it to the id of the last room + 1
		int roomId = _handlerFactory.getRoomManager().getRooms().empty() ? 1 : (_handlerFactory.getRoomManager().getRooms().end() - 1)->id + 1;

		RoomData data = { roomId, request.roomName, request.maxUsers, request.questionsCount, request.answerTimeout, false };
		_handlerFactory.getRoomManager().createRoom(_user, data);

		newHandler = _handlerFactory.createRoomAdminRequestHandler(_user, _handlerFactory.getRoomManager().getRoom(roomId));
	}
	catch (std::exception& e)
	{
		success = false;
	}

	CreateRoomResponse response = { success };
	return { JsonResponsePacketSerializer::serializeResponse(response), newHandler};
}
