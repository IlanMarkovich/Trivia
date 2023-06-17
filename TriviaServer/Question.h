#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Question
{
private:
	// FIELDS
	string _question;
	vector<string> _possibleAnswers;
	int _correctAnswerId;

public:
	// C'tor
	Question(string question, vector<string> possibleAnswer);

	// GETTERS
	string getQuestion() const;
	vector<string> getPossibleAnswers() const;
	int getCorrectAnswerId() const;
};
