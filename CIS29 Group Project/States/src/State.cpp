#include "stdafx.h"
#include "State.h"

const float State::p2pX(const float perc)
{
	return static_cast<float>(renderWindow->getSize().x) * (perc / 100.f);
}

const float State::p2pY(const float perc)
{
	return static_cast<float>(renderWindow->getSize().y) * (perc / 100.f);
}

const unsigned State::calcCharSize()
{
	return static_cast<unsigned>((renderWindow->getSize().x + renderWindow->getSize().y) / 64U);
}

// Constructors / destructors
State::State(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers)
	: renderWindow(move(renderWindow)), states(states),
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

// Functions
std::string State::name() const
{
	std::string name = typeid(*this).name();
#ifdef _MSC_VER       // for MS Visual Studio
	return name.substr(6);
#else                 // for other compilers
	return name.substr(name.find_first_not_of("0123456789"));
#endif
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*renderWindow);
	mousePosView = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow));
}