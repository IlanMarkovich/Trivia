#pragma once

#include "LoggedUser.h"
#include "Question.h"

#include <map>

using std::map;

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};

class Game
{
private:
	// FIELDS
	vector<Question> _questions;
	map<LoggedUser, GameData> _players;
	unsigned int _gameId;

public:
	// C'tors
	Game();
	Game(const vector<Question>& questions, const map<LoggedUser, GameData>& players, unsigned int gameId);

	// GETTERS
	map<LoggedUser, GameData> getPlayers() const;
	unsigned int getId() const;

	// METHODS
	Question getQuestionForUser(const LoggedUser& user) const;
	void submitAnswer(const LoggedUser& user, unsigned int answerId, float answerTime);
	void removePlayer(const LoggedUser& user);
	bool hasGameFinished() const;
};
