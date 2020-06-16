#pragma once

class State
{
private:

protected:
	//Variables
	std::shared_ptr<sf::RenderWindow> renderWindow;

	std::unordered_map<std::string, sf::Texture>* textures;
	std::unordered_map<std::string, sf::Font>* fonts;
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers;
	sf::Sound sound;

	std::stack<std::unique_ptr<State>>* states;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	const float p2pX(const float perc);
	const float p2pY(const float perc);
	const unsigned calcCharSize();

public:
	// Constructors/Destructors
	State(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers);
	virtual ~State();

	// Sound Functions
	void playSound(std::string soundBuffer, float volume);

	virtual std::string name() const;

	// Update
	virtual void updateMousePositions();
	virtual void updateMouseButtons(const sf::Mouse::Button& button) = 0;
	virtual void updateMouseWheel(const short& mouseDelta) = 0;
	virtual void updateKeyboard(const sf::Keyboard::Key& keyCode) = 0;
	virtual void updateState(const float& deltaTime) = 0;

	// Render
	virtual void renderState(std::shared_ptr<sf::RenderTarget> renderTarget) = 0;
};
