#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initializeGUI(sf::Font& font) {
	float width = 250.f;
	float height = 75.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	title.setPosition(0.f, 150.f);
	title.setFont(font);
	title.setString("Paused");
	title.setCharacterSize(56); //26 pixels
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	buttons["RESUME"] = new gui::Button(x, 280, width, height,
		&font, "Resume",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["TUTORIAL_STATE"] = new gui::Button(x, 380, width, height,
		&font, "Help",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["QUIT"] = new gui::Button(x, 480, width, height,
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