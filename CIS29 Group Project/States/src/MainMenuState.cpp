#include "stdafx.h"
#include "MainMenuState.h"
#include "GameState.h"

// Initializers
void MainMenuState::initializeBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->renderWindow->getSize().x),
		static_cast<float>(this->renderWindow->getSize().y)));

	if (!this->backgrounTexture.loadFromFile("Resources/Images/main_menu_background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgrounTexture);
}

void MainMenuState::initializeFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/Motorless-Default.ttf"))
	{ 
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initializeButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(220, 250, 150, 50,
		&this->font, "new game",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS"] = new gui::Button(220, 350, 150, 50,
		&this->font, "settings",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new gui::Button(220, 450, 150, 50,
		&this->font, "quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

// Constructors/Destructors
MainMenuState::MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states)
	: State(renderWindow, states)
{
	this->initializeBackground();
	this->initializeFonts();
	this->initializeButtons();
}

MainMenuState::~MainMenuState()
{
}

/* Functions */
// Update
void MainMenuState::updateInput(unsigned short keyCode)
{
	if (sf::Keyboard::Key::G == keyCode)
		states->push(new GameState(renderWindow, states));
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->renderWindow, this->states));
	}

	//Quit This Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quitState();
	}
}


void MainMenuState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateButtons();
	std::cout << "Running MainMenuState" << std::endl;
}

// Render
void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::renderState(sf::RenderTarget* renderTarget)
{

	if (!renderTarget)
		renderTarget = this->renderWindow;

	renderTarget->draw(background);

	renderTarget->draw(this->background);
	this->renderButtons(renderTarget);
}