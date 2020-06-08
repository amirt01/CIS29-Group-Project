#include "stdafx.h"
#include "State.h"

// Constructors / destructors
State::State(sf::RenderWindow* renderWindow, std::stack<State*>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers)
	: renderWindow(renderWindow), states(states), quit(false),
	textures(textures), fonts(fonts), soundBuffers(soundBuffers)
{
}

State::~State()
{
}

void State::playSound(std::string soundBuffer, float volume)
{
	sound.setBuffer(soundBuffers->at(soundBuffer));
	sound.setVolume(volume);
	sound.play();
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