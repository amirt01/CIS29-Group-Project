#pragma once

#include "State.h"
#include "Button.h"
#include "Leaderboard.h"

class RankingsState
	: public State
{
private:
	// Variables
	sf::RectangleShape background;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;

	Leaderboard* leaderboard;

	// Functions
	// Initializers
	void initializeBackground();
	void initializeGUI();
public:
	RankingsState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		Leaderboard* leaderboard);
	~RankingsState();

	// Update
	void updateMouseButtons(const sf::Mouse::Button& button);
	void updateKeyboard(const sf::Keyboard::Key& keyCode);
	void updateGUI(const float& deltaTime);
	void updateState(const float& deltaTime);
	void updateMouseWheel(const short& mouseDelta) {};

	// Render
	void renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget);
	void renderState(std::shared_ptr<sf::RenderTarget> renderTarget);
};
