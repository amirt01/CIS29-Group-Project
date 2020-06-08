#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initializeGUI(sf::Font& font) {
	float width = 250.f;
	float height = 100.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	buttons["RESUME"] = new gui::Button(x, 100, width, height,
		&font, "Resume",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["TUTORIAL_STATE"] = new gui::Button(x, 300, width, height,
		&font, "Help",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["QUIT"] = new gui::Button(x, 500, width, height,
		&font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

PauseMenu::PauseMenu(sf::RenderWindow* renderWindow, sf::Font& font)
	: Overlay(renderWindow)
{
	initializeGUI(font);
}

PauseMenu::~PauseMenu()
{
}