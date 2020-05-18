#include "stdafx.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "SettingsState.h"

// Initializers
void MainMenuState::initializeBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
									static_cast<float>(renderWindow->getSize().y)));

	if (!backgrounTexture.loadFromFile("Resources/Images/MainMenu.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgrounTexture);
}

void MainMenuState::initializeFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initializeGUI()
{
	buttons["GAME_STATE"] = new gui::Button(220, 250, 150, 50,
		&font, "New Game",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["SETTINGS"] = new gui::Button(220, 350, 150, 50,
		&font, "Settings",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["EXIT_STATE"] = new gui::Button(220, 450, 150, 50,
		&font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}


// Constructors/Destructors
MainMenuState::MainMenuState(sf::RenderWindow* renderWindow, GraphicsSettings& graphicsSettings, std::stack<State*>* states)
	: State(renderWindow, states), graphicsSettings(graphicsSettings)
{
	initializeBackground();
	initializeFonts();
	initializeGUI();
}

MainMenuState::~MainMenuState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

/* Functions */
// Update
void MainMenuState::updateInput(unsigned short keyCode)
{
	if (sf::Keyboard::Key::G == keyCode)
		states->push(new GameState(renderWindow, states));
}

void MainMenuState::updateGUI()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	//New Game
	if (buttons["GAME_STATE"]->isPressed())
	{
		states->push(new GameState(renderWindow, states));
	}
	if (buttons["SETTINGS"]->isPressed())
	{
		states->push(new SettingsState(renderWindow, graphicsSettings, states));
	}
	//Quit This Game
	if (buttons["EXIT_STATE"]->isPressed())
	{
		quitState();
	}
}


void MainMenuState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI();
	std::cout << "Running MainMenuState" << std::endl;
}

// Render
void MainMenuState::renerGUI(sf::RenderTarget* renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->render(renderTarget);
	}
}

void MainMenuState::renderState(sf::RenderTarget* renderTarget)
{

	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);

	renderTarget->draw(background);
	renerGUI(renderTarget);
}