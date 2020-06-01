#include "stdafx.h"
#include "State.h"

// Constructors / destructors
State::State(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: renderWindow(renderWindow), states(states), quit(false)
{
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

std::string State::name() const
{
	std::string name = typeid(*this).name();
#ifdef _MSC_VER       // for MS Visual Studio
	name = name.substr(6);
#else                 // for other compilers
	name = name.substr(name.find_first_not_of("0123456789"));
#endif
	return name;
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*renderWindow);
	mousePosView = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow));
}
