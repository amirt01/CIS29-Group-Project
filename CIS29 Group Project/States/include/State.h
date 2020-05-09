#pragma once
class State
{
private:
	std::vector<sf::Texture> texture;
public:
	State();
	virtual ~State();

	virtual void updateState() = 0;
	virtual void renderState() = 0;
};

