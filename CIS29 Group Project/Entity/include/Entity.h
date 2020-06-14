#pragma once
#include "stdafx.h"
#include "Animation.h"

enum level { TOP = 0, MIDDLE, BOTTOM };

class Entity : public sf::Sprite
{
protected:
	sf::Texture textureSheet;

	std::map<std::string, Animation*> animations;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void addAnimation(const std::string key, float animation_time, int animation_level, int frames, int width, int height);
};