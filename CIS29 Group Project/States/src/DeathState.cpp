#include "stdafx.h"
#include "DeathState.h"

void DeathState::initializeBackground() {
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setFillColor(sf::Color(20, 20, 20, 100));
}

void DeathState::initializeContainer() {
	container.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x) / 4.f,
		static_cast<float>(renderWindow->getSize().y)));

	container.setFillColor(sf::Color(20, 20, 20, 200));

	container.setPosition(static_cast<float>(renderWindow->getSize().x) / 2.f - container.getSize().x / 2.f, 0);
}

void DeathState::initializeFonts() {
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void DeathState::initializeGUI(const float& s) {
	score.setString(std::to_string(s));

	float width = 250.f;
	float height = 100.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	text.setPosition(x, 150);
	text.setString("GAME OVER");
	text.setCharacterSize(26); //26 pixels
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

	score.setPosition(x, 250);
	score.setFont(font);
	score.setCharacterSize(48);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::White);

	buttons["QUIT"] = new gui::Button(x, 480, width, height,
		&font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

DeathState::DeathState(sf::RenderWindow* renderWindow, std::stack<State*>* states, float s)
	: State(renderWindow, states) {
	initializeBackground();
	initializeContainer();
	initializeFonts();
	initializeGUI(s);
}

DeathState::~DeathState() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

/* Functions */
const bool DeathState::isButtonPressed(std::string Button) {
	return buttons[Button]->isPressed();
}

// Update
void DeathState::updateKeyboard(unsigned short keyCode) {
	// Any Unique Death State Keyboard Input
}

void DeathState::updateGUI() {
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}
}

void DeathState::updateMouseWheel(short mouseDelta) {
	// Any Unique Death State Mouse Wheel Input
}

void DeathState::updateState(const float& deltaTime) {
	updateMousePositions();
	updateGUI();
}

// Render
void DeathState::renerGUI(sf::RenderTarget* renderTarget) {
	for (auto& it : buttons) {
		it.second->draw(*renderTarget);
	}
}

void DeathState::renderState(sf::RenderTarget* renderTarget) {
	if (!renderTarget)
		renderTarget = renderWindow;
	renderTarget->draw(background);
	renderTarget->draw(container);
	renerGUI(renderTarget);
}