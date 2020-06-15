#include "stdafx.h"
#include "WinMenu.h"

void WinMenu::initializeGUI(sf::Font* font, sf::SoundBuffer* sound)
{
	float width = 250.f;
	float height = 75.f;
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

	title.setPosition(0.f, 150.f);
	title.setFont(*font);
	title.setString("You Win!");
	title.setCharacterSize(56); //26 pixels
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	score.setPosition(0.f, 250.f);
	score.setFont(*font);
	score.setCharacterSize(48U);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::White);

	buttons["RESTART"] = std::make_unique<gui::Button>(x, 380, width, height,
		font, sound, "Restart",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["QUIT"] = std::make_unique<gui::Button>(x, 480, width, height,
		font, sound, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

WinMenu::WinMenu(std::shared_ptr<sf::RenderWindow> renderWindow, sf::Font* font, sf::SoundBuffer* sound)
	: Overlay(renderWindow)
{
	initializeGUI(font, sound);
}

WinMenu::~WinMenu()
{
}

void WinMenu::setScore(const float& score)
{
	sf::String strScore(std::to_string(score));
	this->score.setString(strScore.substring(0, strScore.find('.') + 3));
}

void WinMenu::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	Overlay::draw(renderTarget, renderStates);

	renderTarget.draw(score, renderStates.transform.translate(container.getPosition().x +
		container.getSize().x / 2.f -
		score.getLocalBounds().width / 2.f, 0.f));
}