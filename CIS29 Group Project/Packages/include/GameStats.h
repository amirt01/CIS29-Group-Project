#pragma once

class GameStats
{
public:
	// Variables
	long coins;
	std::string playerTexture;
	std::string theme;

	GameStats();

	bool loadFromFile(const std::string& path);
	bool writeToFile(const std::string& path);
};
