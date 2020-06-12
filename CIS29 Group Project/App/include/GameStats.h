#pragma once

enum Themes { DAY = 0, NIGHT };

class GameStats
{
public:
	// Variables
	long coins;
	sf::Texture* playerTexture;
	Themes themes;

	GameStats(long coins, sf::Texture* playerTexture, Themes themes);
};
