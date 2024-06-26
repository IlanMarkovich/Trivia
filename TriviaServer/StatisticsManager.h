#pragma once

#include "IDatabase.h"

class StatisticsManager
{
private:
	IDatabase* _database;

public:
	// C'tor
	StatisticsManager(IDatabase* database);

	vector<string> getHighScores() const;
	vector<string> getUserStatistics(string username) const;
};
