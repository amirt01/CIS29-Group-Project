#pragma once

#include "State.h"
#include "Button.h"

class TutorialState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;

	// Initializers
	void initializeGUI();

public:
	// Constructors/Destructors
	TutorialState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
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
	void renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget);
	void renderState(std::shared_ptr<sf::RenderTarget> renderTarget);
};