#pragma once

enum button_States { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui {
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

		// Accessors
		const bool isPressed() const;
		const std::string getText() const;

		// Modifiers
		void setText(const std::string text);

		//Functions
		void update(const sf::Vector2f mousePos);
		void render(sf::RenderTarget* renderTarget);
	};

	class DropDownMenu
	{
	private:
		float clickTime;
		float clickTimeMax;

		sf::Font& font;
		Button* activeElement;
		std::vector<Button*> elements;
		bool showMenu;

	public:
		DropDownMenu(float x, float y, float width, float height, sf::Font& font, std::string listOfTexts[], unsigned numberOfElements, const unsigned default_index = 0);
		~DropDownMenu();

		//Functions
		const bool getClickTime();
		const std::string getActiveElementText();

		void updateClickTime(const float& deltaTime);
		void update(const sf::Vector2f mousePos, const float& deltaTime);
		void render(sf::RenderTarget* renderTarget);
	};
}
