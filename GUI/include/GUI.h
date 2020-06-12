#pragma once

enum button_States { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui {
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
		const sf::Color idleColor;
		const sf::Color hoverColor;
		const sf::Color activeColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, sf::SoundBuffer* sound, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		~Button();

		// Accessors
		const bool getIsActivated();
		const std::string getText() const;

		// Modifiers
		void checkBounds(const sf::Vector2f mousePos);
		void setText(const std::string text);
		virtual void addText(const sf::Keyboard::Key& keycode);

		//Functions
		virtual void updateColor(const sf::Vector2f mousePos);
		virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
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
		DropDownMenu(float x, float y, float width, float height,
			sf::Font&, sf::SoundBuffer* sound, std::string listOfTexts[],
			unsigned numberOfElements, const unsigned default_index = 0);
		~DropDownMenu();

		//Functions
		const bool getClickTime();
		void updateClickTime(const float& deltaTime);
		void update(const sf::Vector2f mousePos, const float& deltaTime);
		void render(sf::RenderTarget* renderTarget);
	};

	class TextBox : public Button
	{
	private:
		enum textBoxState { IDLE = 0, SELECTED } state;

		sf::String defaultText;

	public:
		TextBox(float x, float y, float width, float height,
			sf::Font* font, sf::SoundBuffer* sound, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		~TextBox();

		void updateColor(const sf::Vector2f mousePos);
		void addText(const sf::Keyboard::Key& keycode);

		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
	};
}
