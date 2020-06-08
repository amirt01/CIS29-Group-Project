#pragma once

#include "State.h"
#include "GUI.h"
#include "Leaderboard.h"

class RankingsState
	: public State
{
private:
	// Variables
	sf::RectangleShape background;

	std::map<std::string, gui::Button*> buttons;

	Leaderboard* leaderboard;

	// Functions
	// Initializers
	void initializeBackground();
	void initializeGUI();
public:
	RankingsState(sf::RenderWindow* renderWindow, std::stack<State*>* states,
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
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget);
};
