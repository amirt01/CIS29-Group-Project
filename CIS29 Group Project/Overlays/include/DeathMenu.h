#pragma once

#include "Overlay.h"
#include "GUI.h"

class DeathMenu : public Overlay
{
private:
	sf::Text score;

	bool isInputtingName;

	void initializeGUI(sf::Font& font);
public:
	DeathMenu(sf::RenderWindow* renderWindow, sf::Font& font);
	~DeathMenu();

	void setScore(const float& score);
	void setIsInputtingName(const bool& isInputtingName);

	const bool getIsInputtingName()const;

	void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
};