#include "JsonResponsePacketSerializer.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// PRIVATE METHODS

vector<unsigned char> JsonResponsePacketSerializer::createBuffer(unsigned char code, string data)
{
    vector<unsigned char> buffer = { code };

    string length = std::to_string(data.size());
    buffer.insert(buffer.end(), length.begin(), length.end());

    buffer.insert(buffer.end(), data.begin(), data.end());

    return buffer;
}

// PUBLIC METHODS

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
    json j;
    j["message"] = response.message;

    return createBuffer('1', j.dump());
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
    json j;
    j["status"] = response.status;
    
    return createBuffer('1', j.dump());
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
    json j;
    j["status"] = response.status;

    return createBuffer('1', j.dump());
}
