#include "JsonRequestPacketDeserializer.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// METHODS

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<unsigned char> buffer)
{
	json j = json::parse(buffer);

	return { j["username"].get<string>(), j["password"].get<string>() };
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<unsigned char> buffer)
{
	json j = json::parse(buffer);

	return { j["username"].get<string>(), j["password"].get<string>(), j["email"].get<string>() };
}
