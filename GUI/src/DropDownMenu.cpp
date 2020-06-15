#include "pch.h"
#include "DropDownMenu.h"
namespace gui
{
	DropDownMenu::DropDownMenu(float x, float y, float width, float height,
		sf::Font& font, sf::SoundBuffer* sound, std::string listOfTexts[], unsigned charSize,
		unsigned numberOfElements, const unsigned default_index)
		: font(font), showMenu(false), clickTimeMax(1.f), clickTime(1.f)
	{
		activeElement = new gui::Button(x, y, width, height,
			&font, sound, listOfTexts[default_index], charSize,
			sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

		for (size_t i = 0; i < numberOfElements; i++)
		{
			elements.push_back(new gui::Button(x, y + ((i + 1) * height), width, height,
				&font, sound, listOfTexts[i], charSize,
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
		activeElement->updateColor(mousePos);

		if (activeElement->getIsActivated() && getClickTime())
		{
			showMenu = !showMenu;
		}

		if (showMenu)
		{
			for (auto& it : elements)
			{
				it->updateColor(mousePos);

				if (it->getIsActivated() && getClickTime())
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