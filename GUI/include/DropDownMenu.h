#pragma once

#include "Button.h"

namespace gui
{
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
}