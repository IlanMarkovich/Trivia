#pragma once

#include "Game.h"
#include "Room.h"
#include "IDatabase.h"

class GameManager
{
private:
	// FIELDS
	IDatabase* _database;
	vector<Game> _games;

public:
	// C'tor
	GameManager(IDatabase& database);

	// METHODS
	void createGame(const Room& room);
	void deleteGame(unsigned int gameId);
};
