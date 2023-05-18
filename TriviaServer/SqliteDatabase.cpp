#include "SqliteDatabase.h"

#include <iostream>
#include <io.h>

// Callback functions

int intResultCallback(void* data, int argc, char** argv, char** cols)
{
    if (argv[0] == NULL)
        return -1;

    int* ptr = (int*)data;
    *ptr = atoi(argv[0]);
    return 0;
}

int stringResultCallback(void* data, int argc, char** argv, char** cols)
{
    if (argv[0] == NULL)
        return -1;

    string* ptr = (string*)data;
    *ptr = (string)argv[0];
    return 0;
}

// PUBLIC METHODS

bool SqliteDatabase::open()
{
    // Check if database file already exists
    int file_exists = _access(DATABASE_NAME, 0);
    int result = sqlite3_open(DATABASE_NAME, &_db);

    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to open database!" << std::endl;
        return false;
    }

    // There is no existing database, so we need to create a new one
    if (file_exists != 0)
    {
        string tableQuery = "create table users(name text primary key not null, password text not null, email text not null);";
        char* errMsg = nullptr;
        int queryResult = sqlite3_exec(_db, tableQuery.c_str(), nullptr, nullptr, &errMsg);

        if (queryResult != SQLITE_OK)
        {
            std::cerr << "Failed to create new table! more info: " << errMsg << std::endl;
            return false;
        }
    }

    return true;
}

bool SqliteDatabase::close()
{
    int result = sqlite3_close(_db);
    _db = nullptr;

    return result == SQLITE_OK;
}

int SqliteDatabase::doesUserExist(string username)
{
    string query = "select count(*) from users where username=" + username + ";";
    int result = 0;
    
    selectQuery(query, intResultCallback, &result);
    return result != 0;
}

int SqliteDatabase::doesPasswordMatch(string username, string password)
{
    string query = "select password from users where username=" + username + ";";
    string result;

    selectQuery(query, stringResultCallback, &result);
    return result == password;
}

int SqliteDatabase::addNewUser(string username, string password, string email)
{
    string query = "insert into users (username, password, email) values(";
    query += "\"" + username + "\", \"" + password + "\", \"" + email + "\");";

    tableQuery(query);
    return 1;
}

// PRIVATE METHODS

void SqliteDatabase::tableQuery(string query) const
{
    char* errMsg = nullptr;
    int result = sqlite3_exec(_db, query.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK)
    {
        std::cerr << errMsg << std::endl;
    }
}

void SqliteDatabase::selectQuery(string query, int(*callback)(void*, int, char**, char**), void* data) const
{
    char* errMsg = nullptr;
    int result = sqlite3_exec(_db, query.c_str(), callback, data, &errMsg);

    if (result != SQLITE_OK && string(errMsg) != "query aborted")
    {
        std::cerr << errMsg << std::endl;
    }
}
