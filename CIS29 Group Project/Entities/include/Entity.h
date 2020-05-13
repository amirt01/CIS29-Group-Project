#pragma once

class Entity
{
private:
	void initVariables();

protected:

	sf::Sprite sprite;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);

	//Functions

	void setPosition(const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

