#include "stdafx.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"
#include "LevelEditor.h"
#include "RankingsState.h"
#include "TutorialState.h"
#include "ShopState.h"

// Initializers
void MainMenuState::initializeGUI()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setFillColor(sf::Color(55, 148, 110, 255));

	const float WIDTH = p2pX(14.f);
	const float HEIGHT = p2pY(10.f);

	buttons["FREE_PLAY"] = std::make_unique<gui::Button>(p2pX(25.f) - WIDTH / 2.f, p2pY(35.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Free Play", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_1"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(35.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Level 1", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_2"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(55.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Level 2", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_3"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(75.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Level 3", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["RANKGINGS_STATE"] = std::make_unique<gui::Button>(p2pX(25.f) - WIDTH / 2.f, p2pY(55.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Rankings", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["TUTORIAL_STATE"] = std::make_unique<gui::Button>(p2pX(75.f) - WIDTH / 2.f, p2pY(75.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Tutorial", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["SETTINGS_STATE"] = std::make_unique<gui::Button>(p2pX(75.f) - WIDTH / 2.f, p2pY(35.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Settings", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["SHOP_STATE"] = std::make_unique<gui::Button>(p2pX(75.f) - WIDTH / 2.f, p2pY(55.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Shop", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["EXIT_STATE"] = std::make_unique<gui::Button>(p2pX(25.f) - WIDTH / 2.f, p2pY(75.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Quit", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

// Constructors/Destructors
MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard, GameStats* gameStats, GraphicsSettings* graphicsSettings)
	: State(renderWindow, states, textures, fonts, soundBuffers), leaderboard(leaderboard), gameStats(gameStats), graphicsSettings(graphicsSettings)
{
	initializeGUI();
}

MainMenuState::~MainMenuState()
{
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
		states->push(std::make_unique<FreePlayState>(renderWindow, states, textures, fonts, soundBuffers, leaderboard, gameStats));
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
		states->push(std::make_unique<FreePlayState>(renderWindow, states, textures, fonts, soundBuffers, leaderboard, gameStats));
	if (buttons["LEVEL_1"]->getIsActivated())
		states->push(std::make_unique<Level>(renderWindow, 1, "Config/level1.bin", states, textures, fonts, soundBuffers, leaderboard, gameStats));
	if (buttons["LEVEL_2"]->getIsActivated())
		states->push(std::make_unique<Level>(renderWindow, 2, "Config/level2.bin", states, textures, fonts, soundBuffers, leaderboard, gameStats));
	if (buttons["LEVEL_3"]->getIsActivated())
		states->push(std::make_unique<Level>(renderWindow, 3, "Config/level3.bin", states, textures, fonts, soundBuffers, leaderboard, gameStats));
	if (buttons["RANKGINGS_STATE"]->getIsActivated())
		states->push(std::make_unique<RankingsState>(renderWindow, states, textures, fonts, soundBuffers, leaderboard));
	if (buttons["SETTINGS_STATE"]->getIsActivated())
		states->push(std::make_unique<SettingsState>(renderWindow, states, textures, fonts, soundBuffers, graphicsSettings));
	if (buttons["TUTORIAL_STATE"]->getIsActivated())
		states->push(std::make_unique<TutorialState>(renderWindow, states, textures, fonts, soundBuffers));
	if (buttons["SHOP_STATE"]->getIsActivated())
		states->push(std::make_unique<ShopState>(renderWindow, states, textures, fonts, soundBuffers, gameStats));
	if (buttons["EXIT_STATE"]->getIsActivated())
	{
		using namespace std::chrono_literals; // for ms
		std::this_thread::sleep_for(51ms);
		states->pop();
	}
}

void MainMenuState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI();
}

// Render
void MainMenuState::renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}
}

void MainMenuState::renderState(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	if (background.getSize().x != renderTarget->getSize().x)
	{
		buttons.clear();
		initializeGUI();
	}

	sf::Text title("Rush Hour", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(calcCharSize() * 4U);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);

	sf::RenderStates renderStates;

	renderTarget->draw(background);
	renderTarget->draw(title, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 2.f -
		title.getGlobalBounds().width / 2.f, 0.f)));
	renderGUI(renderTarget);
}