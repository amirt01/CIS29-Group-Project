#pragma once
#include "stdafx.h"
#include "Collision.h"

enum level { TOP = 0, MIDDLE, BOTTOM };

class Entity
{
protected:
	sf::Sprite sprite;

	//Component functions
	void setTexture(sf::Texture& texture, sf::IntRect& intRect);
	void setPosition(const float x, const float y);

public:
	Entity();
	virtual ~Entity();


	void render(sf::RenderTarget* renderTarget);
};