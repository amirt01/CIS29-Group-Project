#include "stdafx.h"
#include "TutorialState.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"

// Initializers
void TutorialState::initializeGUI()
{
	const float WIDTH = p2pX(14.f);
	const float HEIGHT = p2pY(10.f);

	buttons["BACK"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.5f, p2pY(85.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Back", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

// Constructors/Destructors
TutorialState::TutorialState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers)
	: State(renderWindow, states, textures, fonts, soundBuffers)
{
	initializeGUI();

	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setFillColor(sf::Color(55, 148, 110, 255));
}

TutorialState::~TutorialState()
{
}

void TutorialState::updateMouseButtons(const sf::Mouse::Button& button)
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

/* Functions */
// Update
void TutorialState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
	if (sf::Keyboard::Key::Escape == keyCode)
		states->pop();
}

void TutorialState::updateMouseWheel(const short& mouseDelta)
{
}

void TutorialState::updateGUI()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->updateColor(mousePosView);
	}

	if (buttons["BACK"]->getIsActivated())
		states->pop();
}

void TutorialState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI();
}

// Render
void TutorialState::renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}
}

void TutorialState::renderState(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	sf::Text title("Rush Hour", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(calcCharSize() * 4U);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);
	title.setPosition(renderTarget->getSize().x / 2.f - title.getGlobalBounds().width / 2.f, 0.f);

	renderTarget->draw(background);
	renderTarget->draw(title);

	sf::Text text("- Press either W or the Up Arrow to move up a lane.\n"
		"- Press either S or the Down Arrow to move down a lane.\n"
		"- Press the Space Bar to jump over potholes in Levels 2 and 3.\n"
		"- Avoid being hit by cars in the oncoming traffic.\n"
		"- Collect coins scattered in the oncoming traffic to use in the shop.\n"
		"- You have three lives, shown at the top of the screen.\n"
		"- Press the Esc Key to pause the game.\n",
		fonts->at("DOSIS-BOLD")
	);

	text.setFont(fonts->at("DOSIS-BOLD"));
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(calcCharSize());
	text.setPosition(p2pX(50.f) - text.getGlobalBounds().width / 2.f, background.getGlobalBounds().height / 4.0f);

	renderTarget->draw(text);

	renderGUI(renderTarget);
}