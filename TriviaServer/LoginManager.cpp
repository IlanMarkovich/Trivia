#include "LoginManager.h"

#include <algorithm>

LoginManager::LoginManager(IDatabase* database) : _database(database)
{
}

bool LoginManager::signup(string username, string password, string email) const
{
	// Add the new user only if that user doesn't exist
	if (!_database->doesUserExist(username))
	{
		_database->addNewUser(username, password, email);
		return true;
	}

	return false;
}

bool LoginManager::login(string username, string password)
{
	bool isLoggedIn = std::count_if(_loggedUsers.begin(), _loggedUsers.end(), [username](const LoggedUser& user) {
		return user.getUsername() == username;
		});

	// If the user exists, the password is correct and the user isn't already logged in, add this user to the logged users
	if (_database->doesUserExist(username) && _database->doesPasswordMatch(username, password) && !isLoggedIn)
	{
		_loggedUsers.push_back(LoggedUser(username));
		return true;
	}

	return false;
}

void LoginManager::logout(string username)
{
	// This removes the user from the logged user list, by username
	_loggedUsers.erase(std::find_if(_loggedUsers.begin(), _loggedUsers.end(), [username](const LoggedUser& user) {
		return user.getUsername() == username;
		}));
}

LoggedUser& LoginManager::operator[](string username)
{
	return *(std::find_if(_loggedUsers.begin(), _loggedUsers.end(), [username](const LoggedUser& user) {
		return user.getUsername() == username;
		}));
}
