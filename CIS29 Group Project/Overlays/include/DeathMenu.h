#pragma once

#include "Overlay.h"
#include "GUI.h"

class DeathMenu : public Overlay
{
private:
	sf::Text score;

	void initializeGUI(sf::Font* font, sf::SoundBuffer* sound);

public:
	DeathMenu(sf::RenderWindow* renderWindow, sf::Font* font, sf::SoundBuffer* sound);
	~DeathMenu();

	void setScore(const float& score);

	void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
};