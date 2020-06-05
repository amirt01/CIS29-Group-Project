#include "stdafx.h"
#include "TutorialState.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"

// Initializers
void TutorialState::initializeTextures()
{
	if (!textures["BACKGROUND"].loadFromFile("Resources/Images/GameBackground.png"))
		exit(-1); // the loadFromFile() function has an ouput
				  // when it fails so no need to throw
}

void TutorialState::initializeFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
		exit(-1); // the loadFromFile() function has an ouput
				  // when it fails so no need to throw
}

void TutorialState::initializeGUI()
{
	buttons["MAINMENU_STATE"] = new gui::Button(220, 225, 150, 50,
		&font, "Main Menu",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["SETTINGS"] = new gui::Button(220, 350, 150, 50,
		&font, "Settings",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["EXIT_STATE"] = new gui::Button(220, 475, 150, 50,
		&font, "Back",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

// Constructors/Destructors
TutorialState::TutorialState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states)
{
	initializeTextures();
	initializeFonts();
	initializeGUI();

	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setTexture(&textures.at("BACKGROUND"));

}

TutorialState::~TutorialState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

/* Functions */
// Update
void TutorialState::updateInput(unsigned short keyCode)
{
	if (sf::Keyboard::Key::G == keyCode)
		states->push(new FreePlayState(renderWindow, states));
}

void TutorialState::updateGUI()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	if (buttons["MAINMENU_STATE"]->isPressed())
		states->push(new MainMenuState(renderWindow, states));
	if (buttons["SETTINGS"]->isPressed())
		states->push(new SettingsState(renderWindow, states));
	if (buttons["EXIT_STATE"]->isPressed())
		quitState();
}

void TutorialState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI();
}

// Render
void TutorialState::renerGUI(sf::RenderTarget* renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->render(renderTarget);
	}
}

void TutorialState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);

	renderTarget->draw(background);
	renerGUI(renderTarget);
}