#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	// C'tor
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);

	virtual bool isRequestRelevant(RequestInfo info) override;
	virtual RequestResult handleRequest(RequestInfo info) override;

private:
	// FIELDS
	RequestHandlerFactory& _handlerFactory;

	// METHODS
	RequestResult login(RequestInfo info) const;
	RequestResult signup(RequestInfo info) const;
};
