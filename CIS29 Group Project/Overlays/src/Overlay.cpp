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

const float Overlay::p2pX(const float perc)
{
	return std::floor(static_cast<float>(renderWindow->getSize().x) * (perc / 100.f));
}

const float Overlay::p2pY(const float perc)
{
	return std::floor(static_cast<float>(renderWindow->getSize().y) * (perc / 100.f));
}

const unsigned Overlay::calcCharSize()
{
	return static_cast<unsigned>((renderWindow->getSize().x + renderWindow->getSize().y) / 60);
}

Overlay::Overlay(std::shared_ptr<sf::RenderWindow> renderWindow)
	: renderWindow(renderWindow)
{
	initializeBackground();
	initializeContainer();
}

Overlay::~Overlay()
{
}

const std::map<std::string, std::unique_ptr<gui::Button>>* Overlay::getButtons() const
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

	for (auto&& it : buttons)
	{
		it.second->draw(renderTarget);
	}
}