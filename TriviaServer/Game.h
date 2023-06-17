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
	// C'tor
	Game(const vector<Question>& questions, const map<LoggedUser, GameData>& players, unsigned int gameId);

	// METHODS
	Question getQuestionForUser(const LoggedUser& user) const;
	void submitAnswer(const LoggedUser& user, unsigned int answerId);
	void removePlayer(const LoggedUser& user);
};
