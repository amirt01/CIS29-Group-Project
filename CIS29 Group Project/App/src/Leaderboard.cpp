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
	std::ifstream fin;
	fin.open(path);

	if (!fin.is_open())
	{
		std::cout << "Error opening scores file path: " << path << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string name;
	float score;
	time_t date;

	while (fin >> name >> score >> date)
	{
		std::cout << "test" << std::endl;
		addNewScore(name, score, date);
	}

	fin.close();

	return true;
}

bool Leaderboard::writeToFile(const std::string& path)
{
	std::ofstream fout;
	fout.open(path, std::ios::trunc);

	if (!fout.is_open())
	{
		std::cout << "Error opening output file path: " << path << std::endl;
		exit(EXIT_FAILURE);
	}

	auto it = scores.rbegin();
	for (it = scores.rbegin(); it != scores.rend(); ++it)
	{
		fout << it->getName() << ' ' << it->getScore() << ' ' << it->getDate() << '\n';
	}

	fout.close();

	return false;
}

bool Leaderboard::addNewScore(const std::string& name, const float& score, time_t date)
{
	scores.emplace_back(Score(name, score, date));
	scores.sort();

	return true;
}

bool Leaderboard::checkIfHighScore(const float& score)
{
	return scores.front() < score;
}