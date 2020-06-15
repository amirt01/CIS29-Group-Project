#pragma once

#include "Button.h"

class Overlay : public sf::Drawable
{
protected:
	//Variables
	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Text title;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Initializers
	void initializeBackground(std::shared_ptr<sf::RenderWindow> renderWindow);
	void initializeContainer(std::shared_ptr<sf::RenderWindow> renderWindow);
	virtual void initializeGUI(sf::Font* font, sf::SoundBuffer* sound) = 0;

public:
	Overlay(std::shared_ptr<sf::RenderWindow> renderWindow);
	Overlay(const Overlay&) = delete;
	virtual ~Overlay();

	virtual std::string name() const;
	const std::map<std::string, std::unique_ptr<gui::Button>>* getButtons() const;

	virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderTargets = sf::RenderStates::Default) const;
};