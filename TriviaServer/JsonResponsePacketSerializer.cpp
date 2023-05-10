#include "JsonResponsePacketSerializer.h"

// PRIVATE METHODS

vector<unsigned char> JsonResponsePacketSerializer::createBuffer(std::function<json()> serRes, int code)
{
    vector<unsigned char> buffer = { (unsigned char)code };

    string data = serRes().dump();

    for (int i = 0; i < LEN_SIZE; i++)
    {
        buffer.push_back(static_cast<unsigned char>(data.size() >> (8 * (LEN_SIZE - 1 - i))));
    }

    buffer.insert(buffer.end(), data.begin(), data.end());
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
