#pragma once

#include "RoomMemberRequestHandler.h"

class RoomAdminRequestHandler : public RoomMemberRequestHandler
{
public:
	// C'tor
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room);

	// METHODS
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;

private:
	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
};
