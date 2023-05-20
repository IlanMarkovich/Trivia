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
	virtual vector<Question> getQuestions() override;

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

	// Callback functions

	friend int stringResultCallback(void* data, int argc, char** argv, char** cols);
	friend int intResultCallback(void* data, int argc, char** argv, char** cols);
	friend int questionCallback(void* data, int argc, char** argv, char** cols);
};
