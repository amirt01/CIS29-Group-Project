#include "stdafx.h"
#include "TutorialState.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"

// Initializers
void TutorialState::initializeGUI()
{
	const float WIDTH = 150.f;
	const float HEIGHT = 50.f;

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
		quitState();
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
		quitState();
}

void TutorialState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI();
}

// Render
void TutorialState::renerGUI(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}
}

void TutorialState::renderState(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	//if (!renderTarget)
// renderTarget = renderWindow;

	sf::Text title("Rush Hour", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(128);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);

	sf::Text text;
	text.setFont(fonts->at("DOSIS-BOLD"));
	text.setString("Press either W or the Up Arrow to move up a lane.");
	text.setCharacterSize(24);
	title.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(background.getGlobalBounds().width / 20.f - title.getGlobalBounds().width / 10.f, background.getGlobalBounds().height / 4.0f));

	sf::RenderStates renderStates;

	renderTarget->draw(background);
	renderTarget->draw(title, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 2.f -
		title.getGlobalBounds().width / 2.f, 0.f)));
	renderTarget->draw(text, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 5.f -
		title.getGlobalBounds().width / 2.f, 0.f)));
	
	text.setString("Press either S or the Down Arrow to move down a lane.");
	renderTarget->draw(text, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 3.5f -
		title.getGlobalBounds().width / 1.48f, 50.f)));
	
	text.setString("Press the Space Bar to jump over potholes in Levels 2 and 3.");
	renderTarget->draw(text, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 7.f -
		title.getGlobalBounds().width / 2.95f, 50.f)));

	text.setString("Avoid being hit by cars in the oncoming traffic.");
	renderTarget->draw(text, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 7.f -
		title.getGlobalBounds().width / 2.95f, 50.f)));

	text.setString("Collect coins scattered in the oncoming traffic to use in the shop.");
	renderTarget->draw(text, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 7.f -
		title.getGlobalBounds().width / 2.95f, 50.f)));

	text.setString("You have three lives, shown at the top of the screen.");
	renderTarget->draw(text, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 7.f -
		title.getGlobalBounds().width / 2.95f, 50.f)));
		
	text.setString("Press the Esc Key to pause the game.");
	renderTarget->draw(text, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 7.f -
		title.getGlobalBounds().width / 2.95f, 50.f)));
		
	renerGUI(renderTarget);
}