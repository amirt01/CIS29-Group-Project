#include "pch.h"
#include "TextBox.h"

namespace gui
{
	TextBox::TextBox(float x, float y, float width, float height,
		sf::Font* font, sf::SoundBuffer* sound, std::string text, unsigned charSize,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
		: Button(x, y, width, height, font, sound, text, charSize, idleColor, hoverColor, activeColor), state(IDLE),
		defaultText(text)
	{
		this->text.setPosition((x + width / 2.f),
			(y + height / 2.f) - (this->text.getGlobalBounds().height / 2.f) - 7.5f);
	}

	TextBox::~TextBox()
	{
	}

	void TextBox::updateColor(const sf::Vector2f mousePos)
	{
		/*Update the booleans for hover and pressed*/
		//Hover
		if (shape.getGlobalBounds().contains(mousePos) &&
			sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			state = SELECTED;
			shape.setFillColor(hoverColor);

			if (text.getString() == defaultText)
				text.setString("");
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			state = IDLE;
			shape.setFillColor(idleColor);

			if (text.getString() == "")
				text.setString(defaultText);
		}
	}

	void TextBox::addText(const sf::Keyboard::Key& keycode)
	{
		if (state == SELECTED)
			Button::addText(keycode);
	}

	void TextBox::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
	{
		renderTarget.draw(shape, renderStates);
		renderStates.transform.translate(-text.getGlobalBounds().width / 2.f, 0.f);
		renderTarget.draw(text, renderStates);
	}
}