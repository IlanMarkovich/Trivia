#include "SqliteDatabase.h"

#include <iostream>
#include <io.h>

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
