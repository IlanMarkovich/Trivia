#include "LoginRequestHandler.h"

// C'tor

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : _handlerFactory(handlerFactory)
{
}

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
    IRequestHandler* newHandler = databaseResult ? _handlerFactory.createMenuRequestHandler(request.username) : (IRequestHandler*)this;

    return { JsonResponsePacketSerializer::serializeResponse(response), newHandler };
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
    SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    bool databaseResult = _handlerFactory.getLoginManager().signup(request.username, request.password, request.email);

    SignupResponse response = { databaseResult };
    return { JsonResponsePacketSerializer::serializeResponse(response), this };
}
