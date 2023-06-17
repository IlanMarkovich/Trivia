#include "GameManager.h"

// C'tor

GameManager::GameManager(IDatabase* database) : _database(database)
{
}

// METHODS

void GameManager::createGame(const Room& room)
{
	vector<Question> questions = _database->getQuestions(room.getData().numOfQuestionsInGame);
	map<LoggedUser, GameData> players;

	// Add all users to the 'players' map and set to each one
	// an empty game data with the first question as the current question
	for (const LoggedUser& user : room.getAllUsers())
	{
		players[user] = { questions[0], 0, 0, 0 };
	}

	// Create the game and add it to the list of the games
	Game game(questions, players, _games.size());
	_games.push_back(game);
}

void GameManager::deleteGame(unsigned int gameId)
{
	_games.erase(_games.begin() + gameId);
}
