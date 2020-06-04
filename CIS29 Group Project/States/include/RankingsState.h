#pragma once

#include "State.h"
#include "GUI.h"
#include "Leaderboard.h"

class RankingsState
	: public State
{
private:
	// Variables
	sf::Texture backgrounTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	Leaderboard* leaderboard;

	// Functions
	// Initializers
	void initializeBackground();
	void initializeFonts();
	void initializeGUI();
public:
	RankingsState(sf::RenderWindow* renderWindow, std::stack<State*>* states, Leaderboard* leaderboard);
	~RankingsState();

	// Update
	void updateKeyboard(unsigned short keyCode);
	void updateGUI(const float& deltaTime);
	void updateState(const float& deltaTime);
	void updateMouseWheel(short mouseDelta) {};

	// Render
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget);
};
