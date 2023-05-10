#include "JsonResponsePacketSerializer.h"

// PRIVATE METHODS

vector<unsigned char> JsonResponsePacketSerializer::createBuffer(std::function<json()> serRes, int code)
{
    vector<unsigned char> buffer = { code };

    string data = serRes().dump();

    string len = std::to_string(data.size());
    buffer.insert(buffer.end(), len.begin(), len.end());

    return buffer;
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
