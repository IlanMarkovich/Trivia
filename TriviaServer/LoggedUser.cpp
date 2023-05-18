#include "LoggedUser.h"

LoggedUser::LoggedUser(string username) : _username(username)
{
}

string LoggedUser::getUsername() const
{
	return _username;
}
