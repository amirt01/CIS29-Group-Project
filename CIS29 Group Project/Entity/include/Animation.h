#pragma once

class Animation
{
private:
	int frames;
	sf::Vector2u currentImage;

public:
	//Variables
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	float animationTime;
	float timer;
	sf::IntRect textureRect;
	

	Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_time, int animation_level, int frames, int width, int height);

	//Functions
	void update(const float& deltaTime);
};