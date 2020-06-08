#pragma once

#include "Overlay.h"
#include "GUI.h"

class PauseMenu : public Overlay
{
private:
	void initializeGUI(sf::Font& font);

public:
	PauseMenu(sf::RenderWindow* renderWindow, sf::Font& font);
	~PauseMenu();
};
