#include "stdafx.h"
#include "State.h"

// Constructors / destructors
State::State(sf::RenderWindow* renderWindow, std::stack<State*>* states)
{
	this->renderWindow = renderWindow;
	this->states = states;
	quit = false;
	paused = false;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return quit;
}

// Functions
void State::quitState()
{
	quit = true;
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*renderWindow);
	mousePosView = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow));
}
