#pragma once

#include "RoomMemberRequestHandler.h"

class RoomAdminRequestHandler : public RoomMemberRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual void handleRequest(RequestInfo info) override;

private:
	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
};
