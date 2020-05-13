#pragma once
class State
{
protected:
	//Variables
	sf::RenderWindow* renderWindow;
	std::vector<sf::Texture> texture;
	
	bool quit;
	bool paused;

	std::stack<State*>* states;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	// Constructors/Destructors
	State(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~State();

	// Quit State Functions
	const bool& getQuit() const;
	void quitState();

	// Update
	virtual void updateMousePositions();
	virtual void updateInput() = 0;
	virtual void updateState() = 0;

	// Render
	virtual void renderState(sf::RenderTarget* renderTarget = nullptr) = 0;
};

