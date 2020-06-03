#include "stdafx.h"
#include "Leaderboard.h"

bool Leaderboard::addNewScore(const std::string& name, const float& score)
{
	if (scores.size() < MAXNUMBEROFSCORES || scores.back() < score)
	{
		scores.push_back(Score(name, score));

		scores.sort();

		if (scores.size() > MAXNUMBEROFSCORES)
			scores.pop_back();

		return true;
	}

	return false;
}

bool Leaderboard::checkIfHighScore(const float& score)
{
	return scores.front() < score;
}