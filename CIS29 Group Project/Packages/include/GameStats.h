#pragma once
#include "stdafx.h"

class GameStats
{
public:
	// Variables
	long coins;
	std::string playerTexture;
	std::string theme;

	std::unordered_map<std::string, bool> unlocked;

	GameStats();

	bool loadFromFile(const std::string& path);
	bool writeToFile(const std::string& path);
};
