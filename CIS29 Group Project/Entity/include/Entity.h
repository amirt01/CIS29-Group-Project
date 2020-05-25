#pragma once
#include "stdafx.h"
#include "Collision.h"

enum level { TOP = 0, MIDDLE, BOTTOM };

class Entity
{
protected:
	sf::Sprite sprite;

	//Component functions
	void setTexture(sf::Texture& texture);
	void setPosition(const float x, const float y);

public:
	Entity(sf::Texture& texture);
	virtual ~Entity();

	void render(sf::RenderTarget* renderTarget);
};