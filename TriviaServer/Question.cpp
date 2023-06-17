#include "Question.h"

#include <algorithm>

// C'tor

Question::Question(string question, vector<string> possibleAnswers)
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
