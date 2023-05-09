#pragma once

#include <string>
#include <vector>

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
	LoginRequest deserializeLoginRequest(vector<unsigned char> buffer);
	SignupRequest deserializeSignupRequest(vector<unsigned char> buffer);
};
