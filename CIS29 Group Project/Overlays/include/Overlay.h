#pragma once

#include "GUI.h"

class Overlay : public sf::Drawable
{
protected:
	//Variables
	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Text title;

	sf::RenderWindow* renderWindow;

	std::map<std::string, gui::Button*> buttons;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Initializers
	void initializeBackground();
	void initializeContainer();
	virtual void initializeGUI(sf::Font& font) = 0;

public:
	Overlay(sf::RenderWindow* renderWindow);
	Overlay(const Overlay&) = delete;
	virtual ~Overlay();

	virtual std::string name() const;
	const std::map<std::string, gui::Button*>* getButtons() const;

	virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderTargets = sf::RenderStates::Default) const;
};