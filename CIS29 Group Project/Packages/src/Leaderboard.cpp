#include "stdafx.h"
#include "Leaderboard.h"

bool Leaderboard::loadFromFile(sf::Font& font, const std::string& path)
{
	std::ifstream fin;
	fin.open(path);

	if (!fin.is_open())
	{
		return false;
	}

	std::string name;
	float score;
	time_t date;

	while (fin >> name >> score >> date)
		addNewScore(name, score, font, date);

	fin.close();

	return true;
}

bool Leaderboard::writeToFile(const std::string& path)
{
	std::ofstream fout;
	fout.open(path, std::ios::trunc);
	if (!fout.is_open())
	{
		return false;
	}

	std::for_each(scores.rbegin(), scores.rend(),
		[&](Score& score) {fout << score.getName() << ' ' << score.getScore() << ' ' << score.getDate() << '\n'; }
	);

	fout.close();

	return true;
}

bool Leaderboard::addNewScore(const std::string& name, const float& score, sf::Font& font, time_t date)
{
	if (scores.size() < 10)
	{
		scores.emplace_back(Score(name, score, font, date));
		scores.sort();
		return true;
	}
	else if (score > scores.cbegin()->getScore())
	{
		scores.emplace_back(Score(name, score, font, date));
		scores.sort();
		scores.pop_front();
		return true;
	}
	return false;
}

bool Leaderboard::checkIfHighScore(const float& score)
{
	return scores.front() < score;
}

void Leaderboard::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	float x = renderTarget.getSize().x / 2.f - 200.f;
	float y = renderTarget.getSize().y * 0.21f;

	renderStates.transform.translate(x, y);

	std::for_each(scores.crbegin(), scores.crend(),
		[&](Score score) { renderTarget.draw(score, renderStates.transform.translate(0.f, renderTarget.getSize().y * .07f)); }
	);
}