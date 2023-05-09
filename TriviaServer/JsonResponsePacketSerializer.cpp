#include "JsonResponsePacketSerializer.h"

// PRIVATE METHODS

vector<unsigned char> JsonResponsePacketSerializer::createBuffer(std::function<json()> serRes, unsigned char code)
{
    return vector<unsigned char>();
}

// PUBLIC METHODS

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
    return createBuffer([response]() {json j; j["message"] = response.message; return j; }, '1');
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
    return createBuffer([response]() {json j; j["status"] = response.status; return j; }, '1');
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
    return createBuffer([response]() {json j; j["status"] = response.status; return j; }, '1');
}
