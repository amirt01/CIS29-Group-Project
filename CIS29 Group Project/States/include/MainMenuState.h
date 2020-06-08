#pragma once

#include "State.h"
#include "GUI.h"
#include "Leaderboard.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;

	Leaderboard* leaderboard;

	std::unordered_map<std::string, gui::Button*> buttons;

	// Initializers
	void initializeGUI();

public:
	// Constructors/Destructors
	MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
		Leaderboard* leaderboard);
	virtual ~MainMenuState();

	// Update
	void updateMouseWheel(const short& mouseDelta);
	void updateKeyboard(const sf::Keyboard::Key& keyCode);
	void updateMouseButtons(const sf::Mouse::Button& button);
	void updateGUI();
	void updateState(const float& deltaTime);

	// Render
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};