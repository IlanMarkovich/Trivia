#include "RequestHandlerFactory.h"

// C'tor

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : _loginManager(database), _database(database)
{
}
