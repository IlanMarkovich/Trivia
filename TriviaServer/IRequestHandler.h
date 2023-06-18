#pragma once

#include <ctime>
#include <vector>

#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

using std::vector;

class IRequestHandler;

enum RequestType
{
	ERR = -1, LOGIN, SIGNUP, SIGNOUT, 
	GET_ROOMS, GET_PLAYRES_IN_ROOM, GET_PERSONAL_STAT, GET_HIGH_SCORES,
	JOIN_ROOM, CREATE_ROOM, CLOSE_ROOM, START_GAME, GET_ROOM_STATE, LEAVE_ROOM,
	LEAVE_GAME, GET_QUESTION, SUBMIT_ANSWER, GET_GAME_RESULTS
};

struct RequestInfo
{
	RequestType id;
	time_t receivalTime;
	vector<unsigned char> buffer;
};

struct RequestResult
{
	vector<unsigned char> response;
	IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
