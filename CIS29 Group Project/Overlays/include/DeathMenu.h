#pragma once

#include "Overlay.h"
#include "GUI.h"

class DeathMenu : public Overlay
{
private:
	sf::Text score;

	void initializeGUI();
public:
	DeathMenu(sf::RenderWindow* renderWindow);
	~DeathMenu();

	void setScore(const float& score);

	void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
};