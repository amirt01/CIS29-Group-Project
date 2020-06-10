#include "stdafx.h"
#include "DeathMenu.h"

void DeathMenu::initializeGUI(sf::Font& font)
{
	float width = 250.f;
	float height = 75.f;
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

	title.setPosition(0.f, 150.f);
	title.setFont(font);
	title.setString("Game Over!");
	title.setCharacterSize(56); //26 pixels
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	score.setPosition(0.f, 250.f);
	score.setFont(font);
	score.setCharacterSize(48U);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::White);

	buttons["RESTART"] = new gui::Button(x, 380, width, height,
		&font, "Restart",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["QUIT"] = new gui::Button(x, 480, width, height,
		&font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

DeathMenu::DeathMenu(sf::RenderWindow* renderWindow, sf::Font& font)
	: Overlay(renderWindow)
{
	initializeGUI(font);
}

DeathMenu::~DeathMenu()
{
}

void DeathMenu::setScore(const float& score)
{
	sf::String strScore(std::to_string(score));
	this->score.setString(strScore.substring(0, strScore.find('.') + 3));
}

void DeathMenu::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	Overlay::draw(renderTarget, renderStates);

	renderTarget.draw(score, renderStates.transform.translate(container.getPosition().x +
		container.getSize().x / 2.f -
		score.getLocalBounds().width / 2.f, 0.f));
}