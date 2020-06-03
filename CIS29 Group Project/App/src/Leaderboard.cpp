#include "stdafx.h"
#include "Leaderboard.h"

void Leaderboard::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	//renderTarget.draw(sf::RectangleShape(sf::Vector2f(100.f, 100.f)), states);

	float x = 100.f;
	float y = 100.f;

	renderStates.transform.translate(x, y);
	auto it = scores.crbegin();
	for (it = scores.crbegin(); it != scores.crend(); ++it)
	{
		renderStates.transform.translate(0, 50);
		renderTarget.draw(*it, renderStates);
	}
}

bool Leaderboard::loadFromFile(const std::string& path)
{
	return false;
}

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