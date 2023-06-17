#include "Game.h"

// C'tor

Game::Game(const vector<Question>& questions, const map<LoggedUser, GameData>& players, unsigned int gameId)
	: _questions(questions), _players(players), _gameId(gameId)
{
}

// GETTERS

map<LoggedUser, GameData> Game::getPlayers() const
{
	return _players;
}

unsigned int Game::getId() const
{
	return _gameId;
}

// METHODS

Question Game::getQuestionForUser(const LoggedUser& user) const
{
	return _players.at(user).currentQuestion;
}

void Game::submitAnswer(const LoggedUser& user, unsigned int answerId, float answerTime)
{
	GameData& data = _players[user];
	
	if (answerId = data.currentQuestion.getCorrectAnswerId())
	{
		data.correctAnswerCount++;
	}
	else
	{
		data.wrongAnswerCount++;
	}

	// Get the ID of the current question
	int questionId = std::find(_questions.begin(), _questions.end(), data.currentQuestion) - _questions.begin();

	// If the current question is the last one, return an empty question, else get the next question
	data.currentQuestion = questionId == _questions.size() - 1 ? Question() : _questions[questionId + 1];

	// Calculate the new average answer time for this user
	int questionsCount = data.correctAnswerCount + data.wrongAnswerCount;
	float sumAnswerTime = (data.averageAnswerTime * (questionsCount - 1)) + answerTime;
	data.averageAnswerTime = sumAnswerTime / questionsCount;
}

void Game::removePlayer(const LoggedUser& user)
{
	// Check if player is in the map
	if (!_players.count(user))
	{
		return;
	}

	_players.erase(_players.find(user));
}

bool Game::hasGameFinished() const
{
	for (auto i = _players.begin(); i != _players.end(); ++i)
	{
		// If the question isn't empty, it means that this player have not finished the game
		if (i->second.currentQuestion.getQuestion() != "")
		{
			return false;
		}
	}

	return true;
}
