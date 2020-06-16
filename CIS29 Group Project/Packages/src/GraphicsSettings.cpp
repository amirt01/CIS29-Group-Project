#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	gameTitle = "DEFAULT";
	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	verticalSync = false;
	frameRateLimit = 120;
	contextSettings.antialiasingLevel = 0;
	videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions
bool GraphicsSettings::writeToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << gameTitle << std::endl;
		ofs << resolution.width << " " << resolution.height << std::endl;
		ofs << fullscreen << std::endl;
		ofs << frameRateLimit << std::endl;
		ofs << verticalSync << std::endl;
		ofs << contextSettings.antialiasingLevel << std::endl;
	}
	else
	{
		return false;
	}

	ofs.close();
	return true;
}

bool GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, gameTitle);
		ifs >> resolution.width >> resolution.height;
		ifs >> fullscreen;
		ifs >> frameRateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antialiasingLevel;
	}
	else
	{
		return false;
	}

	ifs.close();
	return true;
}