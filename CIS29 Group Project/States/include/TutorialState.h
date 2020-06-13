#pragma once

#include "State.h"
#include "Button.h"

class TutorialState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;

	std::map<std::string, gui::Button*> buttons;

	// Initializers
	void initializeGUI();

public:
	// Constructors/Destructors
	TutorialState(sf::RenderWindow* renderWindow, std::stack<State*>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers);
	virtual ~TutorialState();

	// Update
	void updateMouseButtons(const sf::Mouse::Button& button);
	void updateKeyboard(const sf::Keyboard::Key& keyCode);
	void updateMouseWheel(const short& mouseDelta);

	void updateGUI();
	void updateState(const float& deltaTime);

	// Render
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};