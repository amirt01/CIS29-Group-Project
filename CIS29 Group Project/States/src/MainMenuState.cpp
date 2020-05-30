#include "stdafx.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"

// Initializers
void MainMenuState::initializeBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
									static_cast<float>(renderWindow->getSize().y)));
	try {
		if (!backgrounTexture.loadFromFile("Resources/Images/MainMenu.png"))
		{
			throw std::invalid_argument("Resources/Images/MainMenu.png");
		}
	}
	catch (std::invalid_argument& error)
	{
		exit(-1);
	}

	background.setTexture(&backgrounTexture);
}

void MainMenuState::initializeFonts()
{
	try {
		if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
		{
			throw std::invalid_argument("Resources/Fonts/Dosis-Light.ttf");
		}
	}
	catch (std::invalid_argument& error)
	{
		exit(-1);
	}
}

void MainMenuState::initializeGUI()
{
	buttons["FREE_PLAY"] = new gui::Button(220, 250, 150, 50,
		&font, "Free Play",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_1"] = new gui::Button(520, 250, 150, 50,
		&font, "Level 1",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["SETTINGS"] = new gui::Button(220, 350, 150, 50,
		&font, "Settings",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["EXIT_STATE"] = new gui::Button(220, 450, 150, 50,
		&font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}


// Constructors/Destructors
MainMenuState::MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states)
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
		states->push(new FreePlayState(renderWindow, states));
}

void MainMenuState::updateGUI()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	//New Game
	if (buttons["FREE_PLAY"]->isPressed())
	{
		states->push(new FreePlayState(renderWindow, states));
	}
	if (buttons["LEVEL_1"]->isPressed())
	{
		states->push(new Level(renderWindow, "Config/TestLevel.bin", states));
	}
	if (buttons["SETTINGS"]->isPressed())
	{
		states->push(new SettingsState(renderWindow, states));
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