#pragma once

enum button_States { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	//Core
	unsigned short buttonState;

	//Graphics
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	//Color
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};
