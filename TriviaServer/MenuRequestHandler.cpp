#include "MenuRequestHandler.h"

// C'tor

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager, RoomManager& roomManager, StatisticsManager& statisticsManager, string username)
	: _handlerFactory(handlerFactory), _username(username), _roomManager(roomManager), _statisticsManager(statisticsManager), _loginManager(loginManager)
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

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	bool success = true;

	try
	{
		_loginManager.logout(_username);
	}
	catch (std::exception& e)
	{
		success = false;
	}

	LogoutResponse response = { success };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	GetRoomResponse response = { _roomManager.getRooms().size() > 0, _roomManager.getRooms()};
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
	Room room = _roomManager.getRoom(request.roomId);

	GetPlayersInRoomResponse response = { room.getAllUsers().size() > 0, room.getAllUsers() };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::getPersonalStat(RequestInfo info)
{
	vector<string> statistics = _statisticsManager.getUserStatistics(_username);

	GetPersonalStatResponse response = { !statistics.empty(), statistics };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::getHighScores(RequestInfo info)
{
	vector<string> highScores = _statisticsManager.getHighScores();

	GetHighScoresResponse response = { !highScores.empty(), highScores };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	JoinRoomRequset request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	Room room = _roomManager.getRoom(request.roomId);
}
