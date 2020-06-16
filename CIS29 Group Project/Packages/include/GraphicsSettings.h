#pragma once
class GraphicsSettings
{
public:
	GraphicsSettings();

	//Variables
	std::string gameTitle;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	//Functions
	bool writeToFile(const std::string path);
	bool loadFromFile(const std::string path);
};
