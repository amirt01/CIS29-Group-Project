#pragma once
#include "stdafx.h"
#include "Animation.h"

enum level { TOP = 0, MIDDLE, BOTTOM };

class Entity
{
protected:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	std::map<std::string, Animation*> animations;

	//Component functions
	void setTexture(sf::Texture& texture_sheet);
	void setPosition(const float x, const float y);

public:
	Entity();
	virtual ~Entity();

	sf::Sprite getSprite();

	void addAnimation(const std::string key, float animation_time, int animation_level, int frames, int width, int height);
  
	void render(sf::RenderTarget* renderTarget);
};