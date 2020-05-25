#include "stdafx.h"
#include "Animation.h"

Animation::Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_time, int animation_level, int frames, int width, int height)
	: sprite(sprite), textureSheet(texture_sheet),
	animationTime(animation_time), timer(0.f)
{
	this->frames = frames;
	currentImage.x = 0;
	currentImage.y = animation_level * height;

	textureRect.width = width;
	textureRect.height = height;
}

void Animation::update(const float& deltaTime)
{
	timer += deltaTime;
	if (timer >= animationTime)
	{
		timer -= animationTime;
		currentImage.x++;

		if (currentImage.x >= frames)
		{
			currentImage.x = 0;
		}
	}

	textureRect.left = currentImage.x * textureRect.width;
	textureRect.top = currentImage.y;

	/*std::cout << textureRect.left << "\t" << textureRect.top << std::endl;
	std::cout << textureRect.width << "\t" << textureRect.height << std::endl;
	system("PAUSE");*/
}