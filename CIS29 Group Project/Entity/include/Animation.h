#pragma once

class Animation
{
private:
	unsigned int frames;
	sf::Vector2u currentImage;

public:
	//Variables
	float animationTime;
	float timer;
	sf::IntRect textureRect;

	Animation(float animation_time, int animation_level, unsigned int frames, int width, int height);

	//Functions
	void update(const float& deltaTime);
};