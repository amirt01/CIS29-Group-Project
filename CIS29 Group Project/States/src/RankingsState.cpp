#include "stdafx.h"
#include "RankingsState.h"

void RankingsState::initializeBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	if (!backgrounTexture.loadFromFile("Resources/Images/main_menu_background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgrounTexture);
}

void RankingsState::initializeFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void RankingsState::initializeGUI()
{
	buttons["EXIT_STATE"] = new gui::Button(900.f, 450.f, 150.f, 50.f,
		&font, "Back",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

RankingsState::RankingsState(sf::RenderWindow* renderWindow, std::stack<State*>* states, Leaderboard* leaderboard)
	: State(renderWindow, states), leaderboard(leaderboard)
{
	initializeBackground();
	initializeFonts();
	initializeGUI();
}

RankingsState::~RankingsState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

/* Functions */
// Update
void RankingsState::updateKeyboard(unsigned short keyCode)
{
	if (sf::Keyboard::Key::Escape == keyCode)
		quitState();
}

void RankingsState::updateGUI(const float& deltaTime)
{
	/*Updates all the GUI elements in the state and handles their functionality*/
	// Buttons
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

void RankingsState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI(deltaTime);
}

// Render
void RankingsState::renerGUI(sf::RenderTarget* renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->render(renderTarget);
	}
}

void RankingsState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);
	renderTarget->draw(*leaderboard);
	renerGUI(renderTarget);
}