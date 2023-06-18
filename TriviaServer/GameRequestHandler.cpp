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

		case GET_QUESTIONS:
			result = getQuestions(info);
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
