#pragma once
#include "Entity.h"

class Object : public Entity
{
protected:
	int currentPosition; //might be unnecessary
	int value; //damage or pt value

public:
	Object(short unsigned level, sf::Texture& texture);

	int getCurrentPosition();
	int getValue();

	void move(const float x, const float& deltaTime);

	void setCurrentPosition(int);
	void setValue(int);

	void update(const float& deltaTime);
};