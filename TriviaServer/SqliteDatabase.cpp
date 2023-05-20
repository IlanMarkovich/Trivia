#include "SqliteDatabase.h"

#include <iostream>
#include <io.h>

// Callback functions

int stringResultCallback(void* data, int argc, char** argv, char** cols)
{
    if (argv[0] == NULL)
        return -1;

    string* ptr = (string*)data;
    *ptr = (string)argv[0];
    return 0;
}

int intResultCallback(void* data, int argc, char** argv, char** cols)
{
    if (argv[0] == NULL)
        return -1;

    int* ptr = (int*)data;
    *ptr = atoi(argv[0]);
    return 0;
}

int questionCallback(void* data, int argc, char** argv, char** cols)
{
    vector<Question>* questionsVec = (vector<Question>*)data;
    string text;
    vector<string> answers(NUM_ANSWERS);
    int correctAnswer = 0;

    for (int i = 0; i < argc; i++)
    {
        if (string(cols[i]).find("answer") != string::npos)
        {
            // if col == "answer1", `index` will contain the last number - 1 to acess the correct item in the array `answers`
            string col = cols[i];
            int index = col[col.size() - 1] - '0' - 1;
            answers[index] = argv[i];
        }
        else if (cols[i] == "question")
        {
            text = argv[i];
        }
        else if(cols[i] == "correct")
        {
            correctAnswer = argv[i][0] - '0';
        }
    }

    Question question = { text, answers, correctAnswer };
    questionsVec->push_back(question);

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
        string tableQuery = "create table users(username text primary key not null, password text not null, email text not null);";
        tableQuery += "create table questions(id int primary key not null, question text not null, answer1 text not null, ";
        tableQuery += "answer2 text not null, answer3 text not null, answer4 text not null, correct int not null);";

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
    string query = "select count(*) from users where username=\"" + username + "\";";
    int result = 0;
    
    selectQuery(query, intResultCallback, &result);
    return result != 0;
}

int SqliteDatabase::doesPasswordMatch(string username, string password)
{
    string query = "select password from users where username=\"" + username + "\";";
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

vector<Question> SqliteDatabase::getQuestions()
{
    string query = "select * from questions;";
    vector<Question> questions;

    selectQuery(query, questionCallback, &questions);
    return questions;
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
