#include "GameRequestHandler.h"

// C'tor

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, Game& game, const LoggedUser& user)
	: _handlerFactory(handlerFactory), _game(game), _user(user)
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
	bool success = true;
	Question question;

	try
	{
		question = _game.getQuestionForUser(_user);
	}
	catch (std::exception& e)
	{
		success = false;
	}

	GetQuestionResponse response = { success, question.getQuestion(), question.getPossibleAnswers() };
	return { JsonResponsePacketSerializer::serializeResponse(response), this };
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
	bool success = true;
	int correctAnswerId = _game.getQuestionForUser(_user).getCorrectAnswerId();

	try
	{
		_game.submitAnswer(_user, request.answerId, request.answerTime);

		// After the player's submition, check if the game has finished
		// If it did, finish the game in the game manager
		if (_game.hasGameFinished())
		{
			_handlerFactory.getGameManager().finishGame(_game.getId());
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
	return RequestResult();
}
