#pragma once

#include "State.h"

class GameState :
	public State
{
protected:
	std::stack<State*>* states;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	// Initializers
	void initializeBackground();
public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~GameState();

	// Update
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};