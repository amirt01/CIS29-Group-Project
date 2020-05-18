#pragma once

#include "State.h"
#include "GUI.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgrounTexture;
	GraphicsSettings& graphicsSettings;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	// Initializers
	void initializeBackground();
	void initializeFonts();
	void initializeGUI();

public:
	// Constructors/Destructors
	MainMenuState(sf::RenderWindow* renderWindow, GraphicsSettings& graphicsSettings, std::stack<State*>* states);
	virtual ~MainMenuState();

	// Update
	void updateInput(unsigned short keyCode);
	void updateGUI();
	void updateState(const float& deltaTime);

	// Render
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};