#include "pch.h"
#include "DropDownMenu.h"
namespace gui
{
	DropDownMenu::DropDownMenu(float x, float y, float width, float height,
		sf::Font& font, sf::SoundBuffer* sound, std::string listOfTexts[], unsigned charSize,
		unsigned numberOfElements, const unsigned default_index)
		: font(font), showMenu(false)
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

	Button* DropDownMenu::getActiveElement() const
	{
		return activeElement;
	}

	void DropDownMenu::checkBounds(const sf::Vector2f mousePos)
	{
		activeElement->checkBounds(mousePos);

		for (auto& element : elements)
		{
			element->checkBounds(mousePos);
		}
	}

	void DropDownMenu::update(const sf::Vector2f mousePos)
	{
		activeElement->updateColor(mousePos);

		if (activeElement->getIsActivated())
		{
			showMenu = !showMenu;
		}

		if (showMenu)
		{
			for (auto& it : elements)
			{
				it->updateColor(mousePos);

				if (it->getIsActivated())
				{
					showMenu = false;
					activeElement->setText(it->getText());
				}
			}
		}
	}

	void DropDownMenu::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
	{
		activeElement->draw(renderTarget);

		if (showMenu)
		{
			for (auto& it : elements)
			{
				it->draw(renderTarget);
			}
		}
	}
}