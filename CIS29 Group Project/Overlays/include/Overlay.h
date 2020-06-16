#pragma once

#include "Button.h"

class Overlay : public sf::Drawable
{
protected:
	//Variables
	std::shared_ptr<sf::RenderWindow> renderWindow;

	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Text title;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Initializers
	void initializeBackground();
	void initializeContainer();
	virtual void initializeGUI(sf::Font* font, sf::SoundBuffer* sound) = 0;

	// Functions
	const float p2pX(const float perc);
	const float p2pY(const float perc);
	const unsigned calcCharSize();

public:
	Overlay(std::shared_ptr<sf::RenderWindow> renderWindow);
	Overlay(const Overlay&) = delete;
	virtual ~Overlay();

	const std::map<std::string, std::unique_ptr<gui::Button>>* getButtons() const;

	virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderTargets = sf::RenderStates::Default) const;
};