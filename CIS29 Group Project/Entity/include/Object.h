#pragma once
#include "Entity.h"

enum class Type { Obstacle = 0, Coin };

class Object : public Entity
{
protected:
	int value; //damage or pt value

public:
	bool hit;
	Type type;

	Object(const Type type, const Levels level, sf::Texture& texture, const int width, const int height, const int startingLocation);

	int getValue();

	void setValue(int);

	//void move(const float x, const float& deltaTime);

	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);
};