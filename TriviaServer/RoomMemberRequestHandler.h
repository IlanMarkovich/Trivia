#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
private:
	// FIELDS
	Room _room;
	LoggedUser _user;
	RequestHandlerFactory& _handlerFactory;

	// METHODS
	RequestResult leaveRoom(RequestInfo info);

public:
	// C'tor
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room);

	// METHODS
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;

protected:
	RequestResult getRoomState(RequestInfo info);
};
