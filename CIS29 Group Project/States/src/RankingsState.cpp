#include "stdafx.h"
#include "RankingsState.h"

void RankingsState::initializeBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));
	background.setFillColor(sf::Color(55, 148, 110, 255));
}

void RankingsState::initializeGUI()
{
	const float WIDTH = p2pX(14.f);
	const float HEIGHT = p2pY(10.f);

	buttons["EXIT_STATE"] = std::make_unique<gui::Button>(p2pX(25.f) - WIDTH / 2.f, p2pY(75.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Back", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

RankingsState::RankingsState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard)
	: State(renderWindow, states, textures, fonts, soundBuffers), leaderboard(leaderboard)
{
	initializeBackground();
	initializeGUI();
}

RankingsState::~RankingsState()
{
}

void RankingsState::updateMouseButtons(const sf::Mouse::Button& button)
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
void RankingsState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
	if (sf::Keyboard::Key::Escape == keyCode)
		states->pop();
}

void RankingsState::updateGUI(const float& deltaTime)
{
	/*Updates all the GUI elements in the state and handles their functionality*/
	// Buttons
	for (auto& it : buttons)
	{
		it.second->updateColor(mousePosView);
	}

	//Quit This Game
	if (buttons["EXIT_STATE"]->getIsActivated())
	{
		states->pop();
	}
}

void RankingsState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI(deltaTime);
}

// Render
void RankingsState::renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}
}

void RankingsState::renderState(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	//if (!renderTarget)
	//	renderTarget = renderWindow;

	sf::Text title("Rankings", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(128);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);

	sf::RenderStates renderStates;

	renderTarget->draw(background);
	renderTarget->draw(title, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 2.f -
		title.getGlobalBounds().width / 2.f, 0.f)));
	renderTarget->draw(*leaderboard);
	renderGUI(renderTarget);
}