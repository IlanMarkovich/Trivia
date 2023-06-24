#include "GameRequestHandler.h"

// C'tor

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, Game& game, Room& room, const LoggedUser& user)
	: _handlerFactory(handlerFactory), _game(&game), _room(room), _user(user)
{
}

// PUBLIC METHODS

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id >= LEAVE_GAME && info.id <= GET_GAME_RESULTS;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult result;

	switch (info.id)
	{
		case LEAVE_GAME:
			result = leaveGame(info);
			break;

		case GET_QUESTION:
			result = getQuestion(info);
			break;

		case SUBMIT_ANSWER:
			result = submitAnswer(info);
			break;

		case GET_GAME_RESULTS:
			result = getGameResults(info);
			break;
	}

	return result;
}

// PRIVATE METHODS

RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	Question question;
	bool success = false;

	if (_game != nullptr)
	{
		question = _game->getQuestionForUser(_user);
		success = true;
	}

	GetQuestionResponse response = { success, question.getQuestion(), question.getPossibleAnswers() };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
	bool success = true;
	int correctAnswerId = _game->getQuestionForUser(_user).getCorrectAnswerId();

	try
	{
		_game->submitAnswer(_user, request.answerId, request.answerTime);

		// After the player's submition, check if the game has finished
		// If it did, finish the game in the game manager
		if (_game->hasGameFinished())
		{
			_gameCopy = *_game;
			_handlerFactory.getGameManager().finishGame(_game->getId());
			_game = nullptr;
		}
	}
	catch (std::exception& e)
	{
		success = false;
	}

	SubmitAnswerResponse response = { success, correctAnswerId };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	vector<PlayerResults> gameResults;
	IRequestHandler* newHandler = this;

	// Only if the game is finished, give the game results
	if(_game == nullptr)
	{
		map<LoggedUser, GameData> players = _gameCopy.getPlayers();

		for (auto i = players.begin(); i != players.end(); ++i)
		{
			string username = i->first.getUsername();
			GameData gameData = i->second;

			PlayerResults results = { username, gameData.correctAnswerCount, gameData.wrongAnswerCount, gameData.averageAnswerTime };
			gameResults.push_back(results);
		}

		// Decide what is the new request handler based on if the user is the room admin or not
		newHandler = _room.isAdmin(_user) ? _handlerFactory.createRoomAdminRequestHandler(_user, _room) : _handlerFactory.createRoomMemberRequestHandler(_user, _room);
	}

	GetGameResultsResponse response = { _game == nullptr , gameResults };
	return { JsonResponsePacketSerializer::serializeResponse(response), newHandler};
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	bool success = true;
	IRequestHandler* newHandler = this;

	try
	{
		_game->removePlayer(_user);
		_room.removeUser(_user);

		newHandler = _handlerFactory.createMenuRequestHandler(_user.getUsername());

		// If the user that just left is the last one, delete the game and the room
		if (_game->getPlayers().empty())
		{
			// Finish the game
			_handlerFactory.getGameManager().finishGame(_game->getId());
			
			// Delete the room because no one is there
			_handlerFactory.getRoomManager().deleteRoom(_room.getData().id);
		}
	}
	catch (std::exception& e)
	{
		success = false;
	}

	LeaveGameResponse response = { success };
	return { JsonResponsePacketSerializer::serializeResponse(response), newHandler };
}
