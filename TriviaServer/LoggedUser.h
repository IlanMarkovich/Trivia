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
	bool operator==(const LoggedUser& other) const;
	bool operator<(const LoggedUser& other) const;
};
