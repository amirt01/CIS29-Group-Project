#include "stdafx.h"
#include "MainMenuState.h"
#include "GameState.h"

// Constructors/Destructors
MainMenuState::MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states)
{
	background.setSize(sf::Vector2f(renderWindow->getSize().x, renderWindow->getSize().y));
	background.setFillColor(sf::Color::Cyan);
}

MainMenuState::~MainMenuState()
{
}

/* Functions */
// Update
void MainMenuState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
		states->push(new GameState(renderWindow, states));
}

void MainMenuState::updateState(const float& deltaTime)
{
	updateInput(deltaTime);

	std::cout << "Running MainMenuState" << std::endl;
}

// Render
void MainMenuState::renderState(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(background);
}