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

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(vector<unsigned char> buffer)
{
	json j = json::parse(buffer);
	return { j["roomId"].get<unsigned int>() };
}

JoinRoomRequset JsonRequestPacketDeserializer::deserializeJoinRoomRequest(vector<unsigned char> buffer)
{
	json j = json::parse(buffer);
	return { j["roomId"].get<unsigned int>() };
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(vector<unsigned char> buffer)
{
	json j = json::parse(buffer);
	return { j["roomName"].get<string>(), j["maxUsers"].get<unsigned int>(), j["questionsCount"].get<unsigned int>(), j["answerTimeout"].get<unsigned int>()};
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(vector<unsigned char> buffer)
{
	json j = json::parse(buffer);
	return { j["answerId"].get<unsigned int>() };
}
