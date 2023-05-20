#include "StatisticsManager.h"

// C'tor

StatisticsManager::StatisticsManager(IDatabase* database) : _database(database)
{
}

// METHODS

vector<string> StatisticsManager::getHighScores() const
{
    return _database->getHighScores();
}

vector<string> StatisticsManager::getUserStatistics(string username) const
{
    // If there is no score to that player it means there is no need to return the statistics
    if (_database->getPlayerScore(username) == 0)
    {
        return vector<string>();
    }

    vector<string> statistics = {
        "Average Answer Time: " + std::to_string(_database->getPlayerAverageAnswerTime(username)),
        "Number Of Correct Answers: " + std::to_string(_database->getNumOfCorrectAnswers(username)),
        "Number Of Total Answers: " + std::to_string(_database->getNumOfTotalAnswers(username)),
        "Number Of Player Games: " + std::to_string(_database->getNumOfPlayerGames(username)),
        "Player Score: " + std::to_string(_database->getPlayerScore(username))
    };

    return statistics;
}

void StatisticsManager::updateUserStatistics(string username, float avgAnswerTime, int correctAnswers, int totalAnswers, int playerGames)
{
    _database->updateUserStatistics(username, avgAnswerTime, correctAnswers, totalAnswers, playerGames);
}
