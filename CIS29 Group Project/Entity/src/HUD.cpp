#include "stdafx.h"
#include "HUD.h"

void HUD::initializeContainer()
{
	container.setSize(sf::Vector2f(425.f, 64.f));

	container.setFillColor(sf::Color(20, 20, 20, 200));

	container.setPosition(100.f, container.getSize().y / 2.f);
}

void HUD::initializeFonts() {
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void HUD::initializeScore()
{
	score.setFont(font);
	score.setCharacterSize(48);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::White);
	score.setString(sf::String("0:00"));
	score.setPosition(container.getPosition().x + 10.f, (container.getPosition().y + container.getSize().y / 2) -
														(score.getGlobalBounds().height - 5.f ));
}

void HUD::initializeHearts(sf::Texture& heartTexture)
{
	float position = 1.5 * score.getGlobalBounds().width + score.getPosition().x;
	for (Entity& heart : hearts)
	{
		heart.setTexture(heartTexture);
		heart.setPosition(position += 1.5 * heart.getSprite().getTextureRect().width,
						 (container.getPosition().y + container.getSize().y / 2) -
						 (heart.getSprite().getTextureRect().height / 2) );
	}
}

HUD::HUD(Player* player, sf::Texture& heartTexture)
	: player(player)
{
	initializeContainer();
	initializeFonts();
	initializeScore();
	initializeHearts(heartTexture);
}

HUD::~HUD()
{
}

void HUD::update()
{
	updateScore();
}

void HUD::updateScore()
{
	score.setString(sf::String(std::to_string(player->getCurrentScore())));
}

void HUD::render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(container);

	for (int i = 0; i < player->getCurrentHealth(); i++)
	{
		hearts[i].render(renderTarget);
	}

	renderTarget->draw(score);
}
