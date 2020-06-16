#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initializeGUI(sf::Font* font, sf::SoundBuffer* sound)
{
	const float WIDTH = p2pX(20.f);
	const float HEIGHT = p2pY(10.f);

	title.setPosition(0.f, p2pY(18.f));
	title.setFont(*font);
	title.setString("Paused");
	title.setCharacterSize(calcCharSize() * 1.9f); //26 pixels
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	buttons["RESUME"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(50.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		font, sound, "Resume", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["TUTORIAL_STATE"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(65.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		font, sound, "Help", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["QUIT"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(80.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		font, sound, "Quit", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

PauseMenu::PauseMenu(std::shared_ptr<sf::RenderWindow> renderWindow, sf::Font* font, sf::SoundBuffer* sound)
	: Overlay(renderWindow)
{
	initializeGUI(font, sound);
}

PauseMenu::~PauseMenu()
{
}