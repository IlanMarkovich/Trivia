#pragma once

#include <string>
#include <vector>

#include "Question.h"

using std::string;
using std::vector;

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(string username) = 0;
	virtual int doesPasswordMatch(string username, string password) = 0;
	virtual int addNewUser(string username, string password, string email) = 0;
	virtual vector<Question> getQuestions(int numOfQuestions) = 0;
	virtual float getPlayerAverageAnswerTime(string username) = 0;
	virtual int getNumOfCorrectAnswers(string username) = 0;
	virtual int getNumOfTotalAnswers(string username) = 0;
	virtual int getNumOfPlayerGames(string username) = 0;
	virtual int getPlayerScore(string username) = 0;
	virtual vector<string> getHighScores() = 0;
	virtual void updateUserStatistics(string username, float avgAnswerTime, int correctAnswers, int totalAnswers) = 0;
};
