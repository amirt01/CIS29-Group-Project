#pragma once

class GraphicsSettings
{
public:
	// Variables
	std::string gameTitle;
	sf::VideoMode resolution;
	sf::VideoMode windowBounds;
	bool fullscreen;
	unsigned framerateLimit;
	bool verticalSyncEnabled;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	GraphicsSettings();

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};

