#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initializeBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
									static_cast<float>(renderWindow->getSize().y)));

	if (!backgrounTexture.loadFromFile("Resources/Images/main_menu_background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgrounTexture);
}

void SettingsState::initializeFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initializeButtons()
{
	buttons["EXIT_STATE"] = new gui::Button(220, 450, 150, 50,
		&font, "Main Menu",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

SettingsState::SettingsState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states)
{
	initializeBackground();
	initializeFonts();
	initializeButtons();
}

SettingsState::~SettingsState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

/* Functions */
// Update
void SettingsState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		quitState();
}

void SettingsState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	//Quit This Game
	if (buttons["EXIT_STATE"]->isPressed())
	{
		quitState();
	}
}


void SettingsState::updateState()
{
	updateInput();
	updateMousePositions();
	updateButtons();
	std::cout << "Running MainMenuState" << std::endl;
}

// Render
void SettingsState::renderButtons(sf::RenderTarget* renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->render(renderTarget);
	}
}

void SettingsState::renderState(sf::RenderTarget *renderTarget)
{

	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);

	renderTarget->draw(background);
	renderButtons(renderTarget);
}