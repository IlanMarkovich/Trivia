#include "LoggedUser.h"

// C'tor

LoggedUser::LoggedUser(string username) : _username(username)
{
}

// METHODS

string LoggedUser::getUsername() const
{
	return _username;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	return _username == other._username;
}

bool LoggedUser::operator<(const LoggedUser& other) const
{
	return _username < other._username;
}
