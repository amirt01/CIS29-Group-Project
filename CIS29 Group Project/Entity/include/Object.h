#pragma once
#include "Entity.h"

enum class Type { OBSTACLE = 0, COIN, POTHOLE };

class Object : public Entity
{
protected:
	int value; //damage or pt value

public:
	bool hit;
	Type type;
	Levels level;
	int width;
	int height;

	Object(const Type type, const float posY, const Levels level, sf::Texture& texture, const int width, const int height, const int startingLocation);

	int getValue();
	void setValue(int);

	//void move(const float x, const float& deltaTime);

	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);
};