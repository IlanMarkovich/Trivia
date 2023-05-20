#include "SqliteDatabase.h"

#include <iostream>
#include <io.h>
#include <stdlib.h>

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
    *ptr = std::stoi(argv[0]);
    return 0;
}

int floatResultCallback(void* data, int argc, char** argv, char** cols)
{
    if (argv[0] == NULL)
        return -1;

    float* ptr = (float*)data;
    *ptr = std::atof(argv[0]);
    return 0;
}

int questionCallback(void* data, int argc, char** argv, char** cols)
{
    vector<Question>* questionsVec = (vector<Question>*)data;
    string text;
    vector<string> answers(NUM_ANSWERS);

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
    }

    Question question = { text, answers};
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

        tableQuery += "create table statistics(username text primary key not null, avgAnswerTime float not null, correctAnswers integer not null, ";
        tableQuery += "totalAnswers integer not null, playerGames integer not null);";

        tableQuery += "create table questions(question text primary key not null, answer1 text not null, ";
        tableQuery += "answer2 text not null, answer3 text not null, answer4 text not null);";

        insertQuestions(&tableQuery);

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

vector<Question> SqliteDatabase::getQuestions(int numOfQuestions)
{
    string query = "select * from questions;";
    vector<Question> questions;
    selectQuery(query, questionCallback, &questions);

    if (numOfQuestions < questions.size())
    {
        // Removes questions from the vector to much the number of questions required
        for (int i = 0; i < questions.capacity() - numOfQuestions; i++)
        {
            int randIndex = rand() % questions.size();
            questions.erase(questions.begin() + randIndex);
        }
    }

    return questions;
}

float SqliteDatabase::getPlayerAverageAnswerTime(string username)
{
    return getResultFromStatistics("avgAnswerTime", username);
}

int SqliteDatabase::getNumOfCorrectAnswers(string username)
{
    return (int)getResultFromStatistics("correctAnswers", username);
}

int SqliteDatabase::getNumOfTotalAnswers(string username)
{
    return (int)getResultFromStatistics("totalAnswers", username);
}

int SqliteDatabase::getNumOfPlayerGames(string username)
{
    return (int)getResultFromStatistics("playerGames", username);
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

void SqliteDatabase::insertQuestions(string* queryptr) const
{
    string query = "insert into questions (question, answer1, answer2, answer3, answer4) values";
    query += "(\"In which city, is the Big Nickel located in Canada?\", \"Sudbury, Ontario\", \"Halifax, Nova Scotia\", \"Victoria, British Columbia\", \"Calgary, Alberta\"),";
    query += "(\"What year is on the flag of the US state Wisconsin?\", \"1848\", \"1634\", \"1783\", \"1901\"),";
    query += "(\"How many countries border Kyrgyzstan?\", \"4\", \"3\", \"1\", \"6\"),";
    query += "(\"Which island is located near Wales?\", \"Anglesey\", \"Barry\", \"Bardsey\", \"Caldey\"),";
    query += "(\"What is Canada's largest island?\", \"Baffin Island\", \"Prince Edward Island\", \"Vancouver Island\", \"Newfoundland\"),";
    query += "(\"What is the land connecting North America and South America?\", \"Isthmus of Panama\", \"Isthmus of Suez\", \"Urals\", \"Australasia\"),";
    query += "(\"The Andaman and Nicobar Islands in South East Asia are controlled by which country?\", \"India\", \"Vietnam\", \"Thailand\", \"Indonesia\"),";
    query += "(\"Which is the world's longest river?\", \"Nile\", \"Missouri\", \"Amazon\", \"Yangtze\"),";
    query += "(\"What mountain range lines the border between Spain and France?\", \"Pyrenees\", \"Alps\", \"Carpathians\", \"Urals\"),";
    query += "(\"Which country claims ownership of the disputed state Kosovo?\", \"Serbia\", \"Croatia\", \"Albania\", \"Macedonia\");";

    queryptr->operator+=(query);
}

float SqliteDatabase::getResultFromStatistics(string stat, string username) const
{
    string query = "select " + stat + " from statistics where username=\"" + username + "\";";
    float result = 0;

    selectQuery(query, floatResultCallback, &result);
    return result;
}
