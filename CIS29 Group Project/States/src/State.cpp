#include "stdafx.h"
#include "State.h"

// Constructors / destructors
State::State(sf::RenderWindow* renderWindow, std::stack<State*>* states, std::map<std::string, sf::Texture>* textures)
	: renderWindow(renderWindow), states(states), textures(textures), quit(false)
{
	initializeSounds();
}

State::~State()
{
}

void State::initializeSounds()
{
	for (auto& kv : AUDIO_PATHS)
		if (!soundBuffers[kv.first].loadFromFile(kv.second))
			exit(EXIT_FAILURE); // the loadFromFile() function has an ouput
								// when it fails so no need to throw
}

void State::playSound(std::string soundBuffer, float volume)
{
	sounds.setBuffer(soundBuffers[soundBuffer]);
	sounds.setVolume(volume);
	sounds.play();
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