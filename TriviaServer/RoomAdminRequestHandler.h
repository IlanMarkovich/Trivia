#pragma once

#include "RoomMemberRequestHandler.h"
#include "Game.h"

class RoomAdminRequestHandler : public RoomMemberRequestHandler
{
public:
	// C'tor
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user, Room& room);

	// METHODS
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;

private:
	RequestResult closeRoom(RequestInfo info);
	virtual RequestResult startGame(RequestInfo info) override;
	bool sendToAllInRoom(RequestType id);
};
