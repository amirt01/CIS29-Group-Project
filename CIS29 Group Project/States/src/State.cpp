#include "stdafx.h"
#include "State.h"

// Constructors / destructors
State::State(sf::RenderWindow* renderWindow, std::stack<State*>* states)
{
	this->renderWindow = renderWindow;
	this->states = states;
	quit = false;
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
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->renderWindow);
	this->mousePosView = this->renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->renderWindow));
}
