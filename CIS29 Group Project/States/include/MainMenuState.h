#pragma once

#include "State.h"
#include "Button.h"
#include "Leaderboard.h"
#include "GameStats.h"
#include "GraphicsSettings.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;

	Leaderboard* leaderboard;
	GameStats* gameStats;
	GraphicsSettings* graphicsSettings;

	std::unordered_map<std::string, std::unique_ptr<gui::Button>> buttons;

	// Initializers
	void initializeGUI();

public:
	// Constructors/Destructors
	MainMenuState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		Leaderboard* leaderboard, GameStats* gameStats, GraphicsSettings* graphicsSettings);
	virtual ~MainMenuState();

	// Update
	void updateMouseWheel(const short& mouseDelta);
	void updateKeyboard(const sf::Keyboard::Key& keyCode);
	void updateMouseButtons(const sf::Mouse::Button& button);
	void updateGUI();
	void updateState(const float& deltaTime);

	// Render
	void renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget);
	void renderState(std::shared_ptr<sf::RenderTarget> renderTarget);
};