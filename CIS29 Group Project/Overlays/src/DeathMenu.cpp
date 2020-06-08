#include "stdafx.h"
#include "DeathMenu.h"

void DeathMenu::initializeGUI()
{
	float width = 250.f;
	float height = 100.f;
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

	title.setPosition(x, 150);
	title.setString("GAME OVER");
	title.setCharacterSize(26); //26 pixels
	title.setFillColor(sf::Color::Red);
	title.setStyle(sf::Text::Bold);

	score.setPosition(x, 250);
	score.setFont(font);
	score.setCharacterSize(48);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::White);

	buttons["QUIT"] = new gui::Button(x, 480, width, height,
		&font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

DeathMenu::DeathMenu(sf::RenderWindow* renderWindow)
	: Overlay(renderWindow)
{
	initializeGUI();
}

DeathMenu::~DeathMenu()
{
}

void DeathMenu::setScore(const float& score)
{
	this->score.setString(std::to_string(score));
}

void DeathMenu::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	Overlay::draw(renderTarget, renderStates);
	renderTarget.draw(score);
	renderTarget.draw(title);
}