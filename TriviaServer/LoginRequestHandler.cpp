#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LOGIN;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    // TODO: Implement Login Request Handler

    return RequestResult();
}
