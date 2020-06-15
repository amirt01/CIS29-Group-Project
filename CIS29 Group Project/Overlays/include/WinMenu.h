#pragma once

#include "Overlay.h"

class WinMenu : public Overlay
{
private:
	sf::Text score;

	void initializeGUI(sf::Font* font, sf::SoundBuffer* sound);
public:
	WinMenu(std::shared_ptr<sf::RenderWindow> renderWindow, sf::Font* font, sf::SoundBuffer* sound);
	~WinMenu();

	void setScore(const float& score);

	void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
};
