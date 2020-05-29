#pragma once
#include "Entity.h"

class Object : public Entity
{
protected:
	int currentPosition; //might be unnecessary
	int value; //damage or pt value

public:
	Object(short unsigned level, sf::Texture& texture, int width, int height);

	float getCurrentPosition();
	int getValue();
	const int getWidth() const;

	void setCurrentPosition(int);
	void setValue(int);

	void move(const float x, const float& deltaTime);

	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);
};