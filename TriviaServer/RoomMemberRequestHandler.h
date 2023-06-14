#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomMemberRequestHandler : public IRequestHandler
{
protected:
	Room& _room;
	LoggedUser _user;
	RequestHandlerFactory& _handlerFactory;

public:
	// C'tor
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, Room& room);

	// METHODS
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;

	// GETTER
	LoggedUser getUser() const;

private:
	RequestResult leaveRoom(RequestInfo info);

protected:
	RequestResult getRoomState(RequestInfo info);
	virtual RequestResult startGame(RequestInfo info);
};
