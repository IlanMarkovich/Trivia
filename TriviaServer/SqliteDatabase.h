#pragma once

#include "IDatabase.h"
#include "sqlite3.h"

#define DATABASE_NAME "triviaDB"

class SqliteDatabase : public IDatabase
{
public:
	virtual bool open() override;
	virtual bool close() override;
	virtual int doesUserExist(string username) override;
	virtual int doesPasswordMatch(string username, string password) override;
	virtual int addNewUser(string username, string password, string email) override;

private:
	sqlite3* _db;
};
