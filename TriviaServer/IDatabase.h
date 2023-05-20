#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Question
{
	string text;
	vector<string> answers;
	unsigned int correctAnswer;
};

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(string username) = 0;
	virtual int doesPasswordMatch(string username, string password) = 0;
	virtual int addNewUser(string username, string password, string email) = 0;
	virtual vector<Question> getQuestions() = 0;
};
