#include "JsonRequestPacketDeserializer.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// C'tors

LoginRequest::LoginRequest(string u, string p)
{
	username = u;
	password = p;
}

SignupRequest::SignupRequest(string u, string p, string e)
{
	username = u;
	password = p;
	email = e;
}

// METHODS

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<unsigned char> buffer)
{
	json j = buffer;

	return LoginRequest(j["username"].get<string>(), j["password"].get<string>());
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<unsigned char> buffer)
{
	json j = buffer;

	return SignupRequest(j["username"].get<string>(), j["password"].get<string>(), j["email"].get<string>());
}
