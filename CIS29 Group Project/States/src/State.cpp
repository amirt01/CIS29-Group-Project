#include "stdafx.h"
#include "State.h"

// Initializers
void State::initializeVariables()
{
	quit = 0;
}

// Constructors / destructors
State::State(sf::RenderWindow* renderWindow)
{
	initializeVariables();
	this->renderWindow = renderWindow;
}

State::~State()
{

}
