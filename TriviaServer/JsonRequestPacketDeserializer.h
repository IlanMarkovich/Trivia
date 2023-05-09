#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

struct LoginRequest
{
	LoginRequest(string u, string p);

	string username;
	string password;
};

struct SignupRequest
{
	SignupRequest(string u, string p, string e);

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
