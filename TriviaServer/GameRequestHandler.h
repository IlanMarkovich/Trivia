#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class GameRequestHandler : public IRequestHandler
{
private:
	// FIELDS
	Game& _game;
	LoggedUser _user;
	RequestHandlerFactory& _handlerFactory;

	// METHODS
	RequestResult getQuestions(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);
public:
	// C'tor
	GameRequestHandler(RequestHandlerFactory& handlerFactory, Game& game, const LoggedUser& user);

	// METHODS
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;
};
