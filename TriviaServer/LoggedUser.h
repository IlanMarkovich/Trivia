#pragma once

#include <string>

using std::string;

class LoggedUser
{
private:
	string _username;

public:
	LoggedUser(string username);

	string getUsername() const;
};
