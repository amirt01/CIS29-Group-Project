#pragma once

#include "Overlay.h"
#include "Button.h"

class PauseMenu : public Overlay
{
private:
	void initializeGUI(sf::Font* font, sf::SoundBuffer* sound);

public:
	PauseMenu(std::shared_ptr<sf::RenderWindow> renderWindow, sf::Font* font, sf::SoundBuffer* sound);
	~PauseMenu();
};
