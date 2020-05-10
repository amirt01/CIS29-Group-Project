#pragma once
class State
{
protected:
	//Variables
	sf::RenderWindow* renderWindow;
	std::vector<sf::Texture> texture;
	
	bool quit;

	std::stack<State*>* states;

public:
	// Constructors/Destructors
	State(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~State();

	// Quit State Functions
	const bool& getQuit() const;
	void quitState();

	// Update
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void updateState(const float& deltaTime) = 0;

	// Render
	virtual void renderState(sf::RenderTarget* renderTarget = nullptr) = 0;
};

