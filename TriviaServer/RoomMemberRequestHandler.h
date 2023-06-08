#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

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
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;

protected:
	RequestResult getRoomState(RequestInfo info);
};
