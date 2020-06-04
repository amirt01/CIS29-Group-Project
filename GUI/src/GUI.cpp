#include "pch.h"
#include "GUI.h"

namespace gui {
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
			(shape.getPosition().y + shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height * 1.7f / 2.f)
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
		return buttonState == BTN_ACTIVE;
	}

	const std::string Button::getText() const
	{
		return text.getString();
	}

	// Modifiers
	void Button::setText(const std::string text)
	{
		this->text.setString(text);
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

	void Button::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const
	{
		renderTarget.draw(shape, states);
		renderTarget.draw(text, states);
	}

	/************************* Drop Down List *************************/

	DropDownMenu::DropDownMenu(float x, float y, float width, float height,
		sf::Font& font, std::string listOfTexts[], unsigned numberOfElements, const unsigned default_index)
		: font(font), showMenu(false), clickTimeMax(1.f), clickTime(1.f)
	{
		activeElement = new gui::Button(x, y, width, height,
			&font, listOfTexts[default_index],
			sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

		for (size_t i = 0; i < numberOfElements; i++)
		{
			elements.push_back(new gui::Button(x, y + ((i + 1) * height), width, height,
				&font, listOfTexts[i],
				sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)));
		}
	}

	DropDownMenu::~DropDownMenu()
	{
		delete activeElement;
		for (auto& it : elements)
			delete it;
	}

	const bool DropDownMenu::getClickTime()
	{
		if (clickTime >= clickTimeMax)
		{
			clickTime = 0.f;
			return true;
		}

		return false;
	}

	void DropDownMenu::updateClickTime(const float& deltaTime)
	{
		if (clickTime < clickTimeMax)
			clickTime += 10.f * deltaTime;
	}

	void DropDownMenu::update(const sf::Vector2f mousePos, const float& deltaTime)
	{
		updateClickTime(deltaTime);
		activeElement->update(mousePos);

		if (activeElement->isPressed() && getClickTime())
		{
			showMenu = !showMenu;
		}

		if (showMenu)
		{
			for (auto& it : elements)
			{
				it->update(mousePos);

				if (it->isPressed() && getClickTime())
				{
					showMenu = false;
					activeElement->setText(it->getText());
				}
			}
		}
	}

	void DropDownMenu::render(sf::RenderTarget* renderTarget)
	{
		activeElement->draw(*renderTarget);

		if (showMenu)
		{
			for (auto& it : elements)
			{
				it->draw(*renderTarget);
			}
		}
	}
}