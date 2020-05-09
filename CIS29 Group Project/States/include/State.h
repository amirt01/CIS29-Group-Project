#pragma once
class State
{
private:
	//Variables
	sf::RenderWindow* renderWindow;
	std::vector<sf::Texture> texture;
	
	bool quit;
	//Initializers
	void initializeVariables();
public:
	State(sf::RenderWindow* renderWindow);
	virtual ~State();

	virtual void updateState(const float& deltaTime) = 0;
	virtual void renderState(sf::RenderTarget* renderTarget = nullptr) = 0;
};

