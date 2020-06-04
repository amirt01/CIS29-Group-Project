#pragma once
#include "Entity.h"

enum Type { Obstacle = 0, Coin };

class Object : public Entity
{
protected:
	int currentPosition; //might be unnecessary
	int value; //damage or pt value

public:
	bool hit;
	Type type;

	Object(const Type type, const short unsigned level, sf::Texture& texture, const int width, const int height, const int startingLocation);

	float getCurrentPosition();
	int getValue();
	const float getWidth() const;

	void setCurrentPosition(int);
	void setValue(int);

	void move(const float x, const float& deltaTime);

	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);
};