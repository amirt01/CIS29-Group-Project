#include "stdafx.h"
#include "HUD.h"

void HUD::initializeContainer()
{
	container.setSize(sf::Vector2f(390.f, 64.f));
	container.setFillColor(sf::Color(20, 20, 20, 200));
	container.setPosition(100.f, container.getSize().y / 2.f);
}

void HUD::initializeScore(sf::Font& font)
{
	score.setFont(font);
	score.setCharacterSize(48);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::White);
	score.setString(sf::String("0.00"));
	score.setPosition(container.getPosition().x + 10.f, (container.getPosition().y + container.getSize().y / 2) -
		(score.getGlobalBounds().height - 5.f));
}

void HUD::initializeCoins(sf::Font& font, sf::Texture& coinTexture)
{
	coinBackground.setFillColor(sf::Color(0, 0, 0, 50));
	coinBackground.setSize(sf::Vector2f(200.f, 50.f));
	coinBackground.setPosition(1050, 25);

	coins.setFont(font);
	coins.setCharacterSize(40);
	coins.setStyle(sf::Text::Bold);
	coins.setFillColor(sf::Color::White);
	coins.setPosition(1140, 25);

	coinPic.setSize(sf::Vector2f(75.f, 75.f));
	coinPic.setTexture(&coinTexture);
	coinPic.setPosition(1000, 12);
}

void HUD::initializeHearts(sf::Texture& heartTexture)
{
	float position = score.getGlobalBounds().width + score.getPosition().x;

	std::for_each(hearts.begin(), hearts.end(),
		[&](Entity& heart)
		{
			heart.setTexture(heartTexture);
			heart.setPosition(position += 1.5f * static_cast<float>(heart.getTextureRect().width),
				(container.getPosition().y + container.getSize().y / 2) -
				(heart.getTextureRect().height / 2));
		}
	);
}

HUD::HUD(Player* player, sf::Texture& heartTexture, sf::Texture& coinTexture, sf::Font& font)
	: player(player)
{
	initializeContainer();
	initializeScore(font);
	initializeHearts(heartTexture);
	initializeCoins(font, coinTexture);
}

HUD::~HUD()
{
}

void HUD::update()
{
	updateScore();
	updateCoins();
}

void HUD::updateScore()
{
	sf::String strScore(std::to_string(player->getCurrentScore()));
	score.setString(strScore.substring(0, strScore.find('.') + 3));
}

void HUD::updateCoins()
{
	coins.setString(sf::String(std::to_string(player->getCoins())));
}

void HUD::render(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	renderTarget->draw(container);

	for (int i = 0; i < player->getCurrentHealth(); i++)
		renderTarget->draw(hearts[i]);

	renderTarget->draw(coinBackground);
	renderTarget->draw(coins);
	renderTarget->draw(coinPic);

	renderTarget->draw(score);
}