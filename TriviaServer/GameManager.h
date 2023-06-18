#pragma once

#include "Game.h"
#include "Room.h"
#include "IDatabase.h"

class GameManager
{
private:
	// FIELDS
	IDatabase* _database;
	map<unsigned int, Game> _games;
	static unsigned int _lastGameId;

public:
	// C'tor
	GameManager(IDatabase* database);

	// METHODS
	Game& createGame(const Room& room);
	void finishGame(unsigned int gameId);
	Game& getGame(unsigned int roomId);
};
