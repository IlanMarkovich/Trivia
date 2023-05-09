#include "LoginRequestHandler.h"

// TODO: remove temp include
#include <iostream>

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LOGIN;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    
    std::cout << "username: " << request.username << ", password: " << request.password << std::endl;

    LoginResponse response = { 1 };
    vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeResponse(response);

    return { buffer, nullptr };
}
