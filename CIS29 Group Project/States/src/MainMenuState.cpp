#include "stdafx.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"
#include "LevelEditor.h"
#include "RankingsState.h"
#include "TutorialState.h"
#include "Constants.h"

// Initializers
void MainMenuState::initializeGUI()
{
	buttons["FREE_PLAY"] = new gui::Button(220, 250, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Free Play",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_1"] = new gui::Button(520, 250, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Level 1",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_2"] = new gui::Button(520, 350, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Level 2",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_3"] = new gui::Button(520, 450, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Level 3",
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
	buttons["RANKGINGS_STATE"] = new gui::Button(220, 350, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Rankings",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["TUTORIAL_STATE"] = new gui::Button(920, 450, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Tutorial",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["EXIT_STATE"] = new gui::Button(220, 450, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

// Constructors/Destructors
MainMenuState::MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard)
	: State(renderWindow, states, textures, fonts, soundBuffers), leaderboard(leaderboard)
{
	initializeGUI();

	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setTexture(&textures->at("MAIN_MENU_BACKGROUND"));
}

MainMenuState::~MainMenuState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateMouseWheel(const short& mouseDelta)
{
	// Any Unique Pause State Mouse Wheel Input
}

// Functions

// Update
void MainMenuState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
	if (sf::Keyboard::Key::G == keyCode)
		states->push(new FreePlayState(renderWindow, states, textures, fonts, soundBuffers, leaderboard));
}

void MainMenuState::updateMouseButtons(const sf::Mouse::Button& button)
{
	switch (button)
	{
	case sf::Mouse::Button::Left:
		for (auto& button : buttons)
		{
			button.second->checkBounds(mousePosView);
		}
	default:
		break;
	}
}

void MainMenuState::updateGUI()
{
	// Updates all the buttons in the state and handles their functionality
	for (auto& it : buttons)
	{
		it.second->updateColor(mousePosView);
	}

	if (buttons["FREE_PLAY"]->getIsActivated())
		states->push(new FreePlayState(renderWindow, states, textures, fonts, soundBuffers, leaderboard));
	if (buttons["LEVEL_1"]->getIsActivated())
		states->push(new Level(renderWindow, "Config/level1.bin", states, textures, fonts, soundBuffers, leaderboard));
	if (buttons["LEVEL_2"]->getIsActivated())
		states->push(new Level(renderWindow, "Config/level2.bin", states, textures, fonts, soundBuffers, leaderboard));
	if (buttons["LEVEL_3"]->getIsActivated())
		states->push(new Level(renderWindow, "Config/level3.bin", states, textures, fonts, soundBuffers, leaderboard));
	if (buttons["RANKGINGS_STATE"]->getIsActivated())
		states->push(new RankingsState(renderWindow, states, textures, fonts, soundBuffers, leaderboard));
	if (buttons["TUTORIAL_STATE"]->getIsActivated())
		states->push(new TutorialState(renderWindow, states, textures, fonts, soundBuffers));
	if (buttons["EXIT_STATE"]->getIsActivated())
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
		it.second->draw(*renderTarget);
	}
}

void MainMenuState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);
	renerGUI(renderTarget);
}