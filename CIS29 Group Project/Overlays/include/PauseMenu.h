#pragma once

#include "Overlay.h"
#include "GUI.h"

class PauseMenu : public Overlay
{
private:
	void initializeGUI();

public:
	PauseMenu(sf::RenderWindow* renderWindow);
	~PauseMenu();
};
