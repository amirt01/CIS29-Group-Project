#pragma once
#include "stdafx.h"
#include "Collision.h"
#include "AnimationComponent.h"

enum level { TOP = 0, MIDDLE, BOTTOM };

class Entity
{
protected:
	sf::Sprite sprite;

	AnimationComponent* animationComponent;

	//Component functions
	void setTexture(sf::Texture& texture, sf::IntRect& intRect);
	void setPosition(const float x, const float y);

	void createAnimationComponent(sf::Texture& texture_sheet);

public:
	Entity();
	virtual ~Entity();

	void render(sf::RenderTarget* renderTarget);
};