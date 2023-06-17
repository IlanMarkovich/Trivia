#include "Question.h"

#include <algorithm>

// C'tors

Question::Question() : Question("", vector<string>())
{
}

Question::Question(string question, const vector<string>& possibleAnswers)
	: _question(question)
{
	// The first place is always the correct answer (before the shuffle)
	string correctAnswer = possibleAnswers[0];
	
	// Shuffle the answers randomly
	std::random_shuffle(possibleAnswers.begin(), possibleAnswers.end());

	_possibleAnswers = possibleAnswers;

	// Gets the new position of the correct answer in the vector after the shuffle
	_correctAnswerId = std::find(_possibleAnswers.begin(), _possibleAnswers.end(), correctAnswer) - _possibleAnswers.begin();
}

// GETTERS

string Question::getQuestion() const
{
	return _question;
}

vector<string> Question::getPossibleAnswers() const
{
	return _possibleAnswers;
}

int Question::getCorrectAnswerId() const
{
	return _correctAnswerId;
}
