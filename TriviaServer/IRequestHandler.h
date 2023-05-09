#pragma once

#include <ctime>
#include <vector>

#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

using std::vector;

enum RequestType
{
	LOGIN, SIGNUP
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
