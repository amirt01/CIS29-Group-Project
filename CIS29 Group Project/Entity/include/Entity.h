#pragma once
#include "stdafx.h"
#include "Collision.h"

class Entity {
public:
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;
	sf::Texture texture;

	Entity();
	virtual void update();
	virtual ~Entity();
};