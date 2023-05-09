#include "JsonResponsePacketSerializer.h"

// PRIVATE METHODS

vector<unsigned char> JsonResponsePacketSerializer::createBuffer(std::function<json()> serRes, unsigned char code)
{
    vector<unsigned char> buffer = { code };

    string data = serRes().dump();
    int len = data.size();

    while (len != 0)
    {
        // Enter the byte to the buffer
        buffer.push_back(len & 0xFF);

        // Shift the variable 8 bits (1 byte)
        len >>= 8;
    }

    // Reverse the length (so it will be the original value)
    std::reverse(buffer.begin() + 1, buffer.end());
    
    // Insert the data of the response
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
