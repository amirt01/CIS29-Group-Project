#include "stdafx.h"
#include "SettingsState.h"

// Initializers
void SettingsState::initializeGUI()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setFillColor(sf::Color(55, 148, 110, 255));

	const float WIDTH = p2pX(14.f);
	const float HEIGHT = p2pY(10.f);

	buttons["EXIT_STATE"] = std::make_unique<gui::Button>(p2pX(25.f) - WIDTH / 2.f, p2pY(75.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Back", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["APPLY"] = std::make_unique<gui::Button>(p2pX(50.f) - WIDTH / 2.f, p2pY(75.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Apply", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["FULLSCREEN"] = std::make_unique<gui::Button>(p2pX(25.f) - WIDTH / 2.f, p2pY(35.f) - HEIGHT / 2.f, WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Fullscreen", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	if (graphicsSettings->fullscreen)
	{
		buttons["FULLSCREEN"]->setIdleColor(sf::Color(150, 150, 150, 255));
	}

	//Drop down lists
	std::string resolutions[] = { "2560x1440", "1920x1080", "1280x720" };

	switch (renderWindow->getSize().y)
	{
	case 1440:
		dropDownMenus["RESOLUTION"] = std::make_unique<gui::DropDownMenu>(p2pX(50.f) - WIDTH / 2.f, p2pY(35.f) - HEIGHT / 2.f,
			WIDTH, HEIGHT, fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), resolutions, calcCharSize(), 3, 0);
		break;
	case 1080:
		dropDownMenus["RESOLUTION"] = std::make_unique<gui::DropDownMenu>(p2pX(50.f) - WIDTH / 2.f, p2pY(35.f) - HEIGHT / 2.f,
			WIDTH, HEIGHT, fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), resolutions, calcCharSize(), 3, 1);
		break;
	case 720:
		dropDownMenus["RESOLUTION"] = std::make_unique<gui::DropDownMenu>(p2pX(50.f) - WIDTH / 2.f, p2pY(35.f) - HEIGHT / 2.f,
			WIDTH, HEIGHT, fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), resolutions, calcCharSize(), 3, 2);
		break;
	default:
		dropDownMenus["RESOLUTION"] = std::make_unique<gui::DropDownMenu>(p2pX(50.f) - WIDTH / 2.f, p2pY(35.f) - HEIGHT / 2.f,
			WIDTH, HEIGHT, fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), resolutions, calcCharSize(), 3, 2);
		break;
	}
}

void SettingsState::resetGUI()
{
	dropDownMenus.clear();
	buttons.clear();
	initializeGUI();
}

// Constructors/Destructors
SettingsState::SettingsState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	GraphicsSettings* graphicsSettings)
	: State(renderWindow, states, textures, fonts, soundBuffers), graphicsSettings(graphicsSettings)
{
	initializeGUI();
}

SettingsState::~SettingsState()
{
}

void SettingsState::updateMouseButtons(const sf::Mouse::Button& button)
{
	switch (button)
	{
	case sf::Mouse::Button::Left:
		for (auto& button : buttons)
		{
			button.second->checkBounds(mousePosView);
		}
		for (auto& dropDownMenu : dropDownMenus)
		{
			dropDownMenu.second->checkBounds(mousePosView);
		}
	default:
		break;
	}
}

/* Functions */
// Update
void SettingsState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
	if (sf::Keyboard::Key::Escape == keyCode)
		states->pop();
}

void SettingsState::updateMouseWheel(const short& mouseDelta)
{
}

void SettingsState::updateGUI()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->updateColor(mousePosView);
	}

	// Drop Down Menus
	for (auto& it : dropDownMenus)
	{
		it.second->update(mousePosView);
	}

	if (buttons["FULLSCREEN"]->getIsActivated())
	{
		graphicsSettings->fullscreen = !graphicsSettings->fullscreen;
		if (graphicsSettings->fullscreen)
			buttons["FULLSCREEN"]->setIdleColor(sf::Color(150, 150, 150, 255));
		else
			buttons["FULLSCREEN"]->setIdleColor(sf::Color(100, 100, 100, 200));
	}

	if (buttons["APPLY"]->getIsActivated())
	{
		char width_str[10], height_str[10];

		std::stringstream ss;
		ss << dropDownMenus["RESOLUTION"]->getActiveElement()->getText();
		ss.getline(width_str, 10, 'x');
		ss.getline(height_str, 10);
		graphicsSettings->resolution = sf::VideoMode(atoi(width_str), atoi(height_str));

		if (graphicsSettings->fullscreen)
		{
			renderWindow->create(
				sf::VideoMode::getFullscreenModes()[0],
				graphicsSettings->gameTitle,
				sf::Style::Fullscreen,
				graphicsSettings->contextSettings);
		}
		else
		{
			renderWindow->create(
				graphicsSettings->resolution,
				graphicsSettings->gameTitle,
				sf::Style::Titlebar | sf::Style::Close,
				graphicsSettings->contextSettings);
		}

		resetGUI();
	}

	// Quit This Game
	if (buttons["EXIT_STATE"]->getIsActivated())
	{
		states->pop();
	}
}

void SettingsState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI();
}

// Render
void SettingsState::renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}

	for (auto& it : dropDownMenus)
	{
		it.second->draw(*renderTarget);
	}
}

void SettingsState::renderState(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	//if (!renderTarget)
	//	renderTarget = renderWindow;

	sf::Text title("Rush Hour", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(128);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);

	sf::RenderStates renderStates;

	renderTarget->draw(background);
	renderTarget->draw(title, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 2.f -
		title.getGlobalBounds().width / 2.f, 0.f)));
	renderGUI(renderTarget);
}