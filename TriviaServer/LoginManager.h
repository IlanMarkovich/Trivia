#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class LoginManager
{
private:
	IDatabase* _database;
	vector<LoggedUser> _loggedUsers;

public:
	LoginManager(IDatabase* database);

	bool signup(string username, string password, string email) const;
	bool login(string username, string password);
	void logout(string username);
};
