#include "stdafx.h"
#include "Button.h"

//Constructors/Destructors
Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	buttonState = BTN_IDLE;

	//Shape
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));

	//Text
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(32);
	this->text.setPosition(
		(shape.getPosition().x + shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		(shape.getPosition().y + shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height * 1.7 / 2.f)
	);

	//Color
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	shape.setFillColor(idleColor);
}

Button::~Button()
{
}

//Accessors
const bool Button::isPressed() const
{
	return this->buttonState == BTN_ACTIVE;
}

//Functions

void Button::update(const sf::Vector2f mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	buttonState = BTN_IDLE;

	//Hover
	if (shape.getGlobalBounds().contains(mousePos))
	{
		buttonState = BTN_HOVER;
		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonState = BTN_ACTIVE;
		}
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		break;

	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		break;

	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);

	target->draw(text);
}
