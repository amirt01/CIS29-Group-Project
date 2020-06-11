#pragma once

#include "Overlay.h"

class WinMenu : public Overlay
{
private:
	sf::Text score;

	bool isInputtingName;

	void initializeGUI(sf::Font& font);
public:
	WinMenu(sf::RenderWindow* renderWindow, sf::Font& font);
	~WinMenu();

	void setScore(const float& score);
	void setIsInputtingName(const bool& isInputtingName);

	const bool getIsInputtingName()const;

	void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
};
