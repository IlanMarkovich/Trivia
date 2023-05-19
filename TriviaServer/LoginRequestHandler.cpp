#include "LoginRequestHandler.h"

// PUBLIC METHODS

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LOGIN || info.id == SIGNUP;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    return info.id == LOGIN ? login(info) : signup(info);
}

// PRIVATE METHODS

RequestResult LoginRequestHandler::login(RequestInfo info) const
{
    LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    bool databaseResult = _handlerFactory.getLoginManager().login(request.username, request.password);

    LoginResponse response = { databaseResult };
    return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
}

RequestResult LoginRequestHandler::signup(RequestInfo info) const
{
    SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    bool databaseResult = _handlerFactory.getLoginManager().signup(request.username, request.password, request.email);

    SignupResponse response = { databaseResult };
    return { JsonResponsePacketSerializer::serializeResponse(response), nullptr };
}
