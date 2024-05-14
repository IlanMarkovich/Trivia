#include "GameManager.h"

// Static variable
unsigned int GameManager::_lastGameId = 0;

// C'tor

GameManager::GameManager(IDatabase* database) : _database(database)
{
}

// METHODS

Game& GameManager::createGame(const Room& room)
{
	vector<Question> questions = _database->getQuestions(room.getData().numOfQuestionsInGame);
	Question firstQuestion = questions[0];
	map<LoggedUser, GameData> players;

	// Add all users to the 'players' map and set to each one
	// an empty game data with the first question as the current question
	for (const LoggedUser& user : room.getAllUsers())
	{
		players.insert(std::pair<LoggedUser, GameData>(user, GameData()));
		players[user].currentQuestion = firstQuestion;
	}

	// Create the game and add it to the list of the games
	Game game(questions, players, _lastGameId++);
	_games[room.getData().id] = game;

	return _games[room.getData().id];
}

void GameManager::finishGame(unsigned int gameId)
{
	Game game = std::find_if(_games.begin(), _games.end(), [gameId](const std::pair<unsigned int, Game>& item) {
		return item.second.getId() == gameId;
		})->second;
	auto players = game.getPlayers();

	for (auto i = players.begin(); i != players.end(); ++i)
	{
		string username = i->first.getUsername();
		GameData gameData = i->second;

		_database->updateUserStatistics(username, gameData.averageAnswerTime, gameData.correctAnswerCount, gameData.correctAnswerCount + gameData.wrongAnswerCount);
	}
}

Game& GameManager::getGame(unsigned int roomId)
{
	return _games[roomId];
}
