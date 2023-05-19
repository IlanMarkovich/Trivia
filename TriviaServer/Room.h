#pragma once

#include <string>
#include <vector>

#include "LoginManager.h"

using std::string;
using std::vector;

struct RoomData
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	bool isActive;
};

class Room
{
private:
	RoomData _metadata;
	vector<LoggedUser> _users;

public:
	// C'tor
	Room();
	Room(RoomData metadata);

	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	vector<string> getAllUsers() const;
	RoomData getData() const;
};
