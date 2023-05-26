#pragma once

#include "IDatabase.h"
#include "sqlite3.h"

#define DATABASE_NAME "triviaDB.sqlite"
#define NUM_ANSWERS 4

class SqliteDatabase : public IDatabase
{
public:
	virtual bool open() override;
	virtual bool close() override;
	virtual int doesUserExist(string username) override;
	virtual int doesPasswordMatch(string username, string password) override;
	virtual int addNewUser(string username, string password, string email) override;
	virtual vector<Question> getQuestions(int numOfQuestions) override;
	virtual float getPlayerAverageAnswerTime(string username) override;
	virtual int getNumOfCorrectAnswers(string username) override;
	virtual int getNumOfTotalAnswers(string username) override;
	virtual int getNumOfPlayerGames(string username) override;
	virtual int getPlayerScore(string username) override;
	virtual vector<string> getHighScores() override;
	virtual void updateUserStatistics(string username, float avgAnswerTime, int correctAnswers, int totalAnswers, int playerGames) override;

private:
	sqlite3* _db;

	/// <summary>
	/// Query the database, queries that doesn't recieve a value, ex. INSERT, DELETE, UPDATE
	/// </summary>
	/// <param name="query - ">The query that will be sent to the DB</param>
	void tableQuery(string query) const;

	/// <summary>
	/// Query the database, getting data from it
	/// </summary>
	/// <param name="query - ">The query that will be sent to the DB</param>
	/// <param name="callback - ">The function that transforms the data, from a DB data to the program's data</param>
	/// <param name="data - ">A pointer the where the data will be saved after the query</param>
	void selectQuery(string query, int(*callback)(void*, int, char**, char**), void* data) const;

	/// <summary>
	/// Adds the questions to the questions table (questions are constant)
	/// </summary>
	/// <param name="queryPtr - ">The query that will be sent to the database when created.
	/// The questions insertion will be added to that query</param>
	void insertQuestions(string* queryPtr) const;

	/// <summary>
	/// Get certain data from the statistics table
	/// </summary>
	/// <param name="stat - ">The statistic that its result is required</param>
	/// <param name="username - ">The username which the result belongs to</param>
	float getResultFromStatistics(string stat, string username) const;

	// Callback functions

	friend int stringResultCallback(void* data, int argc, char** argv, char** cols);
	friend int stringsResultCallback(void* data, int argc, char** argv, char** cols);
	friend int intResultCallback(void* data, int argc, char** argv, char** cols);
	friend int floatResultCallback(void* data, int argc, char** argv, char** cols);
	friend int questionCallback(void* data, int argc, char** argv, char** cols);
};
