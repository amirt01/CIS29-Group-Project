#include "stdafx.h"
#include "PauseState.h"

void PauseState::initializeBackground() {
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
									static_cast<float>(renderWindow->getSize().y)));

	if (!backgroundTexture.loadFromFile("Resources/Images/main_menu_background.jpg")) {
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgroundTexture);
}

void PauseState::initializeFonts() {
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void PauseState::initializeButtons() {
	buttons["RESUME"] = new gui::Button(220, 450, 150, 50, &font, "Resume", sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["QUIT"] = new gui::Button(420, 450, 150, 50, &font, "Quit", sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

PauseState::PauseState(sf::RenderWindow * renderWindow, std::stack<State *> * states)
	: State(renderWindow, states) {
	initializeBackground();
	initializeFonts();
	initializeButtons();
}

PauseState::~PauseState() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

/* Functions */
// Update
void PauseState::updateInput(unsigned short keyCode) {
	if (sf::Keyboard::Key::Escape == keyCode)
		quitState();
}

void PauseState::updateButtons() {
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto & it : buttons) {
		it.second->update(mousePosView);
	}

	//Resume or Quit This Game
	if (buttons["RESUME"]->isPressed() || buttons["QUIT"]->isPressed()) {
		quitState();
	}
}


void PauseState::updateState(const float & deltaTime) {
	updateMousePositions();
	updateButtons();
	std::cout << "Running MainMenuState" << std::endl;
}

// Render
void PauseState::renderButtons(sf::RenderTarget * renderTarget) {
	for (auto & it : buttons) {
		it.second->render(renderTarget);
	}
}

void PauseState::renderState(sf::RenderTarget * renderTarget) {

	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);

	renderTarget->draw(background);
	renderButtons(renderTarget);
}