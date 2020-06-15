#pragma once

#include "Button.h"

namespace gui
{
	class TextBox : public Button
	{
	private:
		enum textBoxState { IDLE = 0, SELECTED } state;

		sf::String defaultText;

	public:
		TextBox(float x, float y, float width, float height,
			sf::Font* font, sf::SoundBuffer* sound, std::string text, unsigned charSize,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		~TextBox();

		void updateColor(const sf::Vector2f mousePos);
		void addText(const sf::Keyboard::Key& keycode);

		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
	};
}