#include "LoginManager.h"

#include <algorithm>

LoginManager::LoginManager(IDatabase* database) : _database(database)
{
}

void LoginManager::signup(string username, string password, string email) const
{
	_database->addNewUser(username, password, email);
}

void LoginManager::login(string username, string password)
{
	// If the user exists and the password is correct, add this user to the logged users
	if (_database->doesUserExist(username) && _database->doesPasswordMatch(username, password))
	{
		_loggedUsers.push_back(LoggedUser(username));
	}
}

void LoginManager::logout(string username)
{
	// This removes the user from the logged user list, by username.
	_loggedUsers.erase(std::find(_loggedUsers.begin(), _loggedUsers.end(), [username](LoggedUser user) {return user.getUsername() == username; }));
}
