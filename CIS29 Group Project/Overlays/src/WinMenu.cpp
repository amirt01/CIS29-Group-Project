#include "stdafx.h"
#include "WinMenu.h"

void WinMenu::initializeGUI(sf::Font* font, sf::SoundBuffer* sound)
{
	const float WIDTH = p2pX(20.f);
	const float HEIGHT = p2pY(10.f);

	title.setPosition(0.f, p2pY(18.f));
	title.setFont(*font);
	title.setString("You Win!");
	title.setCharacterSize(static_cast<float>(calcCharSize() * 1.9f));
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	buttons["RESTART"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(65.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		font, sound, "Restart", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["QUIT"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(80.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		font, sound, "Quit", calcCharSize(),
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