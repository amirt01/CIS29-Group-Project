#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	gameTitle = "DEFAULT";
	resolution = sf::VideoMode(1280, 720);
	fullscreen = false;
	framerateLimit = 120;
	windowBounds = sf::VideoMode::getDesktopMode();
	verticalSyncEnabled = false;
	contextSettings.antialiasingLevel = 0;
}

// Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream fout(path);
	if (fout.is_open())
	{
		fout << gameTitle;
		fout << resolution.width << resolution.height;
		fout << fullscreen;
		fout << framerateLimit;
		fout << verticalSyncEnabled;
		fout << contextSettings.antialiasingLevel;
	}
	else
	{
		std::cout << "Error reading file window setting's file. "
			<< "Loading default settings..." << std::endl;
		system("PAUSE");
	}

	fout.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream fin(path);

	/*
	Game Title
	render window width _ render window height
	fullscreen
	framerate limit
	vertical sync enabled
	antialiasing
	*/

	if (fin.is_open())
	{
		std::getline(fin, gameTitle);
		fin >> resolution.width >> resolution.height;
		fin >> fullscreen;
		fin >> framerateLimit;
		fin >> verticalSyncEnabled;
		fin >> contextSettings.antialiasingLevel;
	}
	else
	{
		std::cout << "Error reading file window setting's file. "
			<< "Loading default settings..." << std::endl;
		system("PAUSE");
	}

	fin.close();
}