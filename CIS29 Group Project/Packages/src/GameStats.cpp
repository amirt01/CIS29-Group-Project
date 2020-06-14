#include "stdafx.h"
#include "GameStats.h"
#include "ExceptionHandler.h"

GameStats::GameStats()
	: coins(0), playerTexture("DEFAULT_PLAYER"), theme("DAY")
{

}

bool GameStats::loadFromFile(const std::string& path)
{
	std::ifstream fin(path);

	/*
	number of coins
	player texture
	game theme
	*/

	try
	{
		if (fin.is_open())
		{
			fin >> coins;
			fin >> playerTexture;
			fin >> theme;

			bool isUnlocked;
			fin >> isUnlocked;
			unlocked.insert({"DEFAULT_PLAYER", isUnlocked});
			fin >> isUnlocked;
			unlocked.insert({"BLUE_PLAYER", isUnlocked});
			fin >> isUnlocked;
			unlocked.insert({"DELOREAN_PLAYER", isUnlocked});
		}
		else
			throw exc::LoadFromFileError(path);
	}
	catch (exc::LoadFromFileError&)
	{
		unsigned int in;

		std::cout << "Error reading file window setting's file.\n"
			<< "(1) Load Default Settings\n"
			<< "(2) Exit\n";
		std::cin >> in;

		if (in == 1)
		{
			coins = 0;
			playerTexture = "DEFAULT_PLAYER";
			theme = "GAME_BACKGROUND";
		}
		else
			return false;
	}
	fin.close();

	return true;
}

bool GameStats::writeToFile(const std::string& path)
{
	std::ofstream fout;
	fout.open(path, std::ios::trunc);
	if (!fout.is_open())
	{
		return false;
	}

	fout << coins << '\n';
	fout << playerTexture << '\n';
	fout << theme << '\n';
	fout << unlocked.find("DEFAULT_PLAYER")->second << "\n";
	fout << unlocked.find("BLUE_PLAYER")->second << "\n";
	fout << unlocked.find("DELOREAN_PLAYER")->second << "\n";
	fout.close();

	return true;
}