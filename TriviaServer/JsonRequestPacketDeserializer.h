#pragma once

#include <string>
#include <vector>

#include "IRequestHandler.h"

using std::string;
using std::vector;

struct LoginRequest
{
	string username;
	string password;
};

struct SignupRequest
{
	string username;
	string password;
	string email;
};

class JsonRequestPacketDeserializer
{
public:
	LoginRequest deserializeLoginRequest(RequestInfo info);
	SignupRequest deserializeSignupRequest(RequestInfo info);
};
