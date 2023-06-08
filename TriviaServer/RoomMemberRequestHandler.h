#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
private:
	Room _room;
	LoggedUser _user;
	RequestHandlerFactory& _handlerFactory;

public:
	// C'tor
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room);

	// METHODS
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;

private:
	RequestResult leaveRoom(RequestInfo info);

protected:
	RequestResult getRoomState(RequestInfo info);
};
