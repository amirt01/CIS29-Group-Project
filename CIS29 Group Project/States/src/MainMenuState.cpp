#include "stdafx.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"

// Initializers
void MainMenuState::initializeTextures()
{
	if (!textures["BACKGROUND"].loadFromFile("Resources/Images/MainMenu.png"))
		exit(-1); // the loadFromFile() function has an ouput
				  // when it fails so no need to throw
}

void MainMenuState::initializeFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
		exit(-1); // the loadFromFile() function has an ouput
				  // when it fails so no need to throw
}

void MainMenuState::initializeGUI()
{
	buttons["FREE_PLAY"] = new gui::Button(220, 250, 150, 50,
		&font, "Free Play",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_1"] = new gui::Button(520, 250, 150, 50,
		&font, "Level 1",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_2"] = new gui::Button(520, 350, 150, 50,
		&font, "Level 2",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_3"] = new gui::Button(520, 450, 150, 50,
		&font, "Level 3",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	/*
	buttons["LEVEL_4"] = new gui::Button(720, 250, 150, 50,
		&font, "Level 4",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_5"] = new gui::Button(720, 350, 150, 50,
		&font, "Level 5",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_6"] = new gui::Button(720, 450, 150, 50,
		&font, "Level 6",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_7"] = new gui::Button(920, 250, 150, 50,
		&font, "Level 7",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_8"] = new gui::Button(920, 350, 150, 50,
		&font, "Level 8",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_9"] = new gui::Button(920, 450, 150, 50,
		&font, "Level 9",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	*/
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
	initializeTextures();
	initializeFonts();
	initializeGUI();

	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setTexture(&textures.at("BACKGROUND"));
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

	if (buttons["FREE_PLAY"]->isPressed())
		states->push(new FreePlayState(renderWindow, states));
	if (buttons["LEVEL_1"]->isPressed())
		states->push(new Level(renderWindow, "Config/level1.bin", states));
	if (buttons["LEVEL_2"]->isPressed())
		states->push(new Level(renderWindow, "Config/level2.bin", states));
	if (buttons["LEVEL_3"]->isPressed())
		states->push(new Level(renderWindow, "Config/level3.bin", states));
	if (buttons["SETTINGS"]->isPressed())
		states->push(new SettingsState(renderWindow, states));
	if (buttons["EXIT_STATE"]->isPressed())
		quitState();
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