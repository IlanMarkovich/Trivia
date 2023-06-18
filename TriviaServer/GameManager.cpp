#include "GameManager.h"

// Static variable
unsigned int GameManager::_lastGameId = 0;

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
	Game game(questions, players, _lastGameId++);
	_games.push_back(game);
}

void GameManager::finishGame(unsigned int gameId)
{
	Game game = *(std::find_if(_games.begin(), _games.end(), [gameId](const Game& game) {
		return game.getId() == gameId;
		}));
	auto players = game.getPlayers();

	for (auto i = players.begin(); i != players.end(); ++i)
	{
		string username = i->first.getUsername();
		GameData gameData = i->second;

		_database->updateUserStatistics(username, gameData.averageAnswerTime, gameData.correctAnswerCount, gameData.correctAnswerCount + gameData.wrongAnswerCount);
	}

	// Deletes the game with this game id from the list of games
	_games.erase(std::find_if(_games.begin(), _games.end(), [gameId](const Game& game) {
		return game.getId() == gameId;
		}));
}
