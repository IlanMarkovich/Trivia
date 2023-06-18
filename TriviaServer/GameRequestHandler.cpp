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
}
