#include "pch.h"
#include "GUI.h"

namespace gui {
	const sf::String keyCodeToChar(const sf::Keyboard::Key& keyCode)
	{
		switch (keyCode) {
		case sf::Keyboard::A: return("a");
		case sf::Keyboard::B: return("b");
		case sf::Keyboard::C: return("c");
		case sf::Keyboard::D: return("d");
		case sf::Keyboard::E: return("e");
		case sf::Keyboard::F: return("f");
		case sf::Keyboard::G: return("g");
		case sf::Keyboard::H: return("h");
		case sf::Keyboard::I: return("i");
		case sf::Keyboard::J: return("j");
		case sf::Keyboard::K: return("k");
		case sf::Keyboard::L: return("l");
		case sf::Keyboard::M: return("m");
		case sf::Keyboard::N: return("n");
		case sf::Keyboard::O: return("o");
		case sf::Keyboard::P: return("p");
		case sf::Keyboard::Q: return("q");
		case sf::Keyboard::R: return("r");
		case sf::Keyboard::S: return("s");
		case sf::Keyboard::T: return("t");
		case sf::Keyboard::U: return("u");
		case sf::Keyboard::V: return("v");
		case sf::Keyboard::W: return("w");
		case sf::Keyboard::X: return("x");
		case sf::Keyboard::Y: return("y");
		case sf::Keyboard::Z: return("z");
		case sf::Keyboard::Num0: return("0");
		case sf::Keyboard::Num1: return("1");
		case sf::Keyboard::Num2: return("2");
		case sf::Keyboard::Num3: return("3");
		case sf::Keyboard::Num4: return("4");
		case sf::Keyboard::Num5: return("5");
		case sf::Keyboard::Num6: return("6");
		case sf::Keyboard::Num7: return("7");
		case sf::Keyboard::Num8: return("8");
		case sf::Keyboard::Num9: return("9");
		case sf::Keyboard::LBracket: return("[");
		case sf::Keyboard::RBracket: return("]");
		case sf::Keyboard::SemiColon: return(";");
		case sf::Keyboard::Comma: return(",");
		case sf::Keyboard::Period: return(".");
		case sf::Keyboard::Quote: return("\"");
		case sf::Keyboard::Slash: return("/");
		case sf::Keyboard::BackSlash: return("\\");
		case sf::Keyboard::Tilde: return("~");
		case sf::Keyboard::Equal: return("=");
		case sf::Keyboard::Space: return(" ");
		case sf::Keyboard::Return: return("\n");
		case sf::Keyboard::BackSpace: return("BackSpace");
		case sf::Keyboard::Delete: return("Delete");
		case sf::Keyboard::Add: return("+");
		case sf::Keyboard::Subtract: return("-");
		case sf::Keyboard::Multiply: return("*");
		case sf::Keyboard::Divide: return("/");
		case sf::Keyboard::Numpad0: return("0");
		case sf::Keyboard::Numpad1: return("1");
		case sf::Keyboard::Numpad2: return("2");
		case sf::Keyboard::Numpad3: return("3");
		case sf::Keyboard::Numpad4: return("4");
		case sf::Keyboard::Numpad5: return("5");
		case sf::Keyboard::Numpad6: return("6");
		case sf::Keyboard::Numpad7:	return("7");
		case sf::Keyboard::Numpad8:	return("8");
		case sf::Keyboard::Numpad9:	return("9");
		default: return("Unknow");
		}
	}

	//Constructors/Destructors
	Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
		: idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
	{
		//Shape
		shape.setPosition(sf::Vector2f(x, y));
		shape.setSize(sf::Vector2f(width, height));

		//Text
		this->text.setFont(*font);
		this->text.setString(text);
		this->text.setCharacterSize(32);
		this->text.setPosition((x + width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
			(y + height / 2.f) - (this->text.getGlobalBounds().height / 2.f) - 7.5f);

		//Color
		shape.setFillColor(idleColor);
	}

	Button::~Button()
	{
	}

	const bool Button::getIsActivated()
	{
		if (isActivated)
		{
			isActivated = false;
			return true;
		}

		return false;
	}

	const std::string Button::getText() const
	{
		return text.getString();
	}

	void Button::checkBounds(const sf::Vector2f mousePos)
	{
		// Activate the button if the mouse is within the button bounds
		isActivated = shape.getGlobalBounds().contains(mousePos);
	}

	// Modifiers
	void Button::setText(const std::string text)
	{
		this->text.setString(text);
	}

	void Button::addText(const sf::Keyboard::Key& keycode)
	{
		if (keyCodeToChar(keycode) == "BackSpace")
			text.setString(text.getString().substring(0, text.getString().getSize() - 1));
		else if (keyCodeToChar(keycode) == "Unknow")
			return;
		else if (keyCodeToChar(keycode) == "\n")
			return;
		else if (text.getString().getSize() < 9)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
			{
				char c = std::toupper(*keyCodeToChar(keycode).getData());
				text.setString(text.getString() + sf::String(c));
			}
			else
				text.setString(text.getString() + keyCodeToChar(keycode));
	}

	// Functions

	void Button::updateColor(const sf::Vector2f mousePos)
	{
		// Idle
		shape.setFillColor(idleColor);

		// Hover
		if (shape.getGlobalBounds().contains(mousePos))
		{
			shape.setFillColor(hoverColor);
			// Pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				shape.setFillColor(activeColor);
			}
		}
	}

	void Button::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
	{
		renderTarget.draw(shape, renderStates);
		renderTarget.draw(text, renderStates);
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

	const sf::String keyCodeToChar(const sf::Keyboard::Key& keyCode);

	TextBox::TextBox(float x, float y, float width, float height, sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
		: Button(x, y, width, height, font, text, idleColor, hoverColor, activeColor), state(IDLE),
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