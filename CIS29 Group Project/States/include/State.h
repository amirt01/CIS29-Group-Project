#pragma once
class State
{
private:
	//Variables
	sf::RenderWindow* renderWindow;
	std::vector<sf::Texture> texture;
	
	bool quit;
public:
	State(sf::RenderWindow* renderWindow);
	virtual ~State();

	// Quit State Functions
	const bool& getQuit() const;
	void quitState();

	// Update
	virtual void updateKeybinds(const float& deltaTime) = 0;
	virtual void updateState(const float& deltaTime) = 0;

	// Render
	virtual void renderState(sf::RenderTarget* renderTarget = nullptr) = 0;
};

