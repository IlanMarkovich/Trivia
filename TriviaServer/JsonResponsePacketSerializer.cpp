#include "JsonResponsePacketSerializer.h"

#include <sstream>
#include <iterator>
#include <algorithm>

// PRIVATE METHODS

vector<unsigned char> JsonResponsePacketSerializer::createBuffer(std::function<json()> serRes)
{
    vector<unsigned char> buffer = { '\0' };
    string data = serRes().dump();

    // Convert from int to bytes
    for (int i = 0; i < LEN_SIZE; i++)
    {
        buffer.push_back(static_cast<unsigned char>(data.size() >> (8 * (LEN_SIZE - 1 - i))));
    }

    buffer.insert(buffer.end(), data.begin(), data.end());
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeOnlyStatusResponse(unsigned int status)
{
    return createBuffer([status]() {
        json j;
        j["status"] = status;
        return j;
        });
}

vector<unsigned char> JsonResponsePacketSerializer::serializeStatusAndStrVecResponse(unsigned int status, const vector<string>& vec, string fieldName)
{
    return createBuffer([status, vec, fieldName]() {
        json j;

        j["status"] = status;

        std::stringstream strStream;
        std::ostream_iterator<string> iter(strStream, "\n");
        std::copy(vec.begin(), vec.end(), iter);
        j[fieldName] = strStream.str();

        return j;
        });
}

// PUBLIC METHODS

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
    return createBuffer([response]() {
        json j; 
        j["message"] = response.message; 
        return j;
        });
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
    return serializeOnlyStatusResponse(response.status);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
    return serializeOnlyStatusResponse(response.status);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse response)
{
    return serializeOnlyStatusResponse(response.status);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomResponse response)
{
    return createBuffer([response]() {
        json j; 
        j["status"] = response.status; 
        j["rooms"] = Room::roomDataVecToString(response.rooms); 
        return j; 
        });
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse response)
{
    return serializeStatusAndStrVecResponse(response.status, response.players, "players");
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetHighScoresResponse response)
{
    return serializeStatusAndStrVecResponse(response.status, response.players, "players");
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPersonalStatResponse response)
{
    return serializeStatusAndStrVecResponse(response.status, response.statistics, "statistics");
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response)
{
    return serializeOnlyStatusResponse(response.status);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response)
{
    return serializeOnlyStatusResponse(response.status);
}
