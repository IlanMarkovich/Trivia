#include "LoginRequestHandler.h"

// TODO: remove temp include
#include <iostream>

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LOGIN || info.id == SIGNUP;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    if (info.id == LOGIN)
    {
        LoginRequest login_request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
        std::cout << "username: " << login_request.username << ", password: " << login_request.password << std::endl;
    }
    else
    {
        SignupRequest signup_request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
        std::cout << "username: " << signup_request.username << ", password: " << signup_request.password << ", email: " << signup_request.email << std::endl;
    }

    LoginResponse response = { 1 };
    vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeResponse(response);

    return { buffer, nullptr };
}
