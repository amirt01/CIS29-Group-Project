#pragma once

#include "Button.h"

namespace gui
{
	class DropDownMenu : public sf::Drawable
	{
	private:
		sf::Font& font;
		Button* activeElement;
		std::vector<Button*> elements;
		bool showMenu;

	public:
		DropDownMenu(float x, float y, float width, float height,
			sf::Font&, sf::SoundBuffer* sound, std::string listOfTexts[], unsigned charSize,
			unsigned numberOfElements, const unsigned default_index = 0);
		~DropDownMenu();

		//Functions
		Button* getActiveElement() const;
		void checkBounds(const sf::Vector2f mousePos);

		void update(const sf::Vector2f mousePos);
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const;
	};
}