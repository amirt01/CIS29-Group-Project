#pragma once

namespace gui
{
	enum class button_States { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

	const sf::String keyCodeToChar(const sf::Keyboard::Key& keyCode);

	class Button : public sf::Drawable
	{
	protected:
		//Core
		bool isActivated;

		//Graphics
		sf::RectangleShape shape;
		sf::Sound sound;
		sf::Text text;

		//Color
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, sf::SoundBuffer* sound, std::string text, unsigned charSize,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		~Button();

		// Accessors
		const bool getIsActivated();
		const std::string getText() const;

		// Modifiers
		void checkBounds(const sf::Vector2f mousePos);
		void setText(const std::string text);
		virtual void addText(const sf::Keyboard::Key& keycode);

		void setIdleColor(const sf::Color& color);
		void setHoverColor(const sf::Color& color);
		void setActiveColor(const sf::Color& color);

		//Functions
		virtual void updateColor(const sf::Vector2f mousePos);
		virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
	};
}