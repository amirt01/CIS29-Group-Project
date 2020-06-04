#include "stdafx.h"
#include "PauseState.h"

void PauseState::initializeBackground() {
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setFillColor(sf::Color(20, 20, 20, 100));
}

void PauseState::initializeContainer()
{
	container.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x) / 4.f,
		static_cast<float>(renderWindow->getSize().y)));

	container.setFillColor(sf::Color(20, 20, 20, 200));

	container.setPosition(static_cast<float>(renderWindow->getSize().x) / 2.f - container.getSize().x / 2.f, 0);
}

void PauseState::initializeFonts() {
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void PauseState::initializeGUI() {
	float width = 250.f;
	float height = 100.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	buttons["RESUME"] = new gui::Button(x, 200, width, height,
		&font, "Resume",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["QUIT"] = new gui::Button(x, 400, width, height,
		&font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

PauseState::PauseState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states) {
	initializeBackground();
	initializeContainer();
	initializeFonts();
	initializeGUI();
}

PauseState::~PauseState() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

/* Functions */
const bool PauseState::isButtonPressed(std::string Button)
{
	return buttons[Button]->isPressed();
}

// Update
void PauseState::updateKeyboard(unsigned short keyCode) {
	// Any Unique Pause State Keyboard Input
}

void PauseState::updateGUI() {
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}
}

void PauseState::updateMouseWheel(short mouseDelta)
{
	// Any Unique Pause State Mouse Wheel Input
}

void PauseState::updateState(const float& deltaTime) {
	updateMousePositions();
	updateGUI();

	std::cout << "Running PauseState" << std::endl;
}

// Render
void PauseState::renerGUI(sf::RenderTarget* renderTarget) {
	for (auto& it : buttons) {
		it.second->draw(*renderTarget);
	}
}

void PauseState::renderState(sf::RenderTarget* renderTarget) {
	if (!renderTarget)
		renderTarget = renderWindow;
	renderTarget->draw(background);
	renderTarget->draw(container);
	renerGUI(renderTarget);
}