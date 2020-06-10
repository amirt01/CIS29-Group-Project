#include "stdafx.h"
#include "Overlay.h"

void Overlay::initializeBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setFillColor(sf::Color(20, 20, 20, 100));
}

void Overlay::initializeContainer()
{
	container.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x) / 4.f,
		static_cast<float>(renderWindow->getSize().y)));

	container.setFillColor(sf::Color(20, 20, 20, 200));

	container.setPosition(static_cast<float>(renderWindow->getSize().x) / 2.f - container.getSize().x / 2.f, 0);
}

Overlay::Overlay(sf::RenderWindow* renderWindow)
	: renderWindow(renderWindow)
{
	initializeBackground();
	initializeContainer();
}

Overlay::~Overlay()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::string Overlay::name() const
{
	std::string name = typeid(*this).name();
#ifdef _MSC_VER       // for MS Visual Studio
	name = name.substr(6);
#else                 // for other compilers
	name = name.substr(name.find_first_not_of("0123456789"));
#endif
	return name;
}

const std::map<std::string, gui::Button*>* Overlay::getButtons() const
{
	return &buttons;
}

void Overlay::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	renderTarget.draw(background);
	renderTarget.draw(container);

	renderTarget.draw(title, renderStates.transform.translate(container.getPosition().x +
		container.getSize().x / 2.f -
		title.getLocalBounds().width / 2.f, 0.f));

	for (auto it : buttons)
	{
		it.second->draw(renderTarget);
	}
}