#include "stdafx.h"
#include "HUD.h"

void HUD::initializeHearts(sf::Texture& heartTexture)
{
	float position = 0.5;
	for (Entity& heart : hearts)
	{
		heart.setTexture(heartTexture);
		heart.setPosition(position += 75, 10.f);
	}
}

HUD::HUD(Player* player, sf::Texture& heartTexture)
	: player(player)
{
	initializeHearts(heartTexture);
}

HUD::~HUD()
{
}

void HUD::update()
{
}

void HUD::render(sf::RenderTarget* renderTarget)
{
	for (int i = 0; i < player->getCurrentHealth(); i++)
	{
		hearts[i].render(renderTarget);
	}
}
