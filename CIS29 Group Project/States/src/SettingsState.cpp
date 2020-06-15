#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initializeBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	if (!backgrounTexture.loadFromFile("Resources/Images/main_menu_background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgrounTexture);
}

void SettingsState::initializeFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initializeGUI()
{
	buttons["APPLY_SETTINGS"] = new gui::Button(700.f, 450.f, 150.f, 50.f,
		&font, "Apply",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["EXIT_STATE"] = new gui::Button(900.f, 450.f, 150.f, 50.f,
		&font, "Back",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	std::string resolutions[] = { "1920x1080", "800x600", "640x480" };
	dropDownMenus["RESOLUTION"] = new gui::DropDownMenu(400.f, 200.f, 200.f, 50.f, font, resolutions, 3);
}

SettingsState::SettingsState(sf::RenderWindow* renderWindow, GraphicsSettings& graphicsSettings, std::stack<State*>* states)
	: State(renderWindow, states), graphicsSettings(graphicsSettings)
{
	initializeBackground();
	initializeFonts();
	initializeGUI();
}

SettingsState::~SettingsState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = dropDownMenus.begin();
	for (it2 = dropDownMenus.begin(); it2 != dropDownMenus.end(); ++it2)
	{
		delete it2->second;
	}
}

/* Functions */
// Update
void SettingsState::updateInput(unsigned short keyCode)
{
	if (sf::Keyboard::Key::Escape == keyCode)
		quitState();
}

void SettingsState::updateGUI(const float& deltaTime)
{
	/*Updates all the GUI elements in the state and handles their functionality*/
	// Buttons
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	// Apply Settings

	/* THIS FUNCTION IS HELLA SCUFFED AND NEEDS TO BE UPDATED */
	if (buttons["APPLY_SETTINGS"]->isPressed())
	{
		char width_str[10], height_str[10];

		std::stringstream ss;
		ss << dropDownMenus["RESOLUTION"]->getActiveElementText();
		ss.getline(width_str, 10, 'x');
		ss.getline(height_str, 10);
		graphicsSettings.resolution = sf::VideoMode(atoi(width_str), atoi(height_str));

		renderWindow->create(graphicsSettings.resolution, graphicsSettings.gameTitle, sf::Style::Titlebar | sf::Style::Close, graphicsSettings.contextSettings);
	}

	// Quit This Game
	if (buttons["EXIT_STATE"]->isPressed())
	{
		quitState();
	}

	// Drop Down Menus
	for (auto& it : dropDownMenus)
	{
		it.second->update(mousePosView, deltaTime);
	}
}

void SettingsState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI(deltaTime);
}

// Render
void SettingsState::renerGUI(sf::RenderTarget* renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}

	for (auto& it : dropDownMenus)
	{
		it.second->render(renderTarget);
	}
}

void SettingsState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);

	renderTarget->draw(background);
	renerGUI(renderTarget);
}