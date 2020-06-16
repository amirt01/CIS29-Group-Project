#include "stdafx.h"
#include "ShopState.h"

void ShopState::initializeGUI() {
	const float BUTTONWIDTH = p2pX(14.f);
	const float BUTTONHEIGHT = p2pY(10.f);

	buttons["BACK"] = std::make_unique<gui::Button>(p2pX(93.f) - BUTTONWIDTH / 2.f, p2pY(93.f) - BUTTONHEIGHT / 2.f, BUTTONWIDTH, BUTTONHEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Back", calcCharSize(),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	const float WIDTH = p2pX(20.f);
	const float HEIGHT = p2pY(28.f);

	buttons["PLAYER1"] = std::make_unique<gui::Button>(p2pX(8.f), p2pY(18.f), WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "", calcCharSize(),
		sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	buttons["PLAYER2"] = std::make_unique<gui::Button>(p2pX(37.f), p2pY(18.f), WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "", calcCharSize(),
		sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	buttons["PLAYER3"] = std::make_unique<gui::Button>(p2pX(65.f), p2pY(18.f), WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "", calcCharSize(),
		sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	buttons["MAP1"] = std::make_unique<gui::Button>(p2pX(8.f), p2pY(60.f), WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "", calcCharSize(),
		sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	buttons["MAP2"] = std::make_unique<gui::Button>(p2pX(37.f), p2pY(60.f), WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "", calcCharSize(),
		sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	buttons["MAP3"] = std::make_unique<gui::Button>(p2pX(65.f), p2pY(60.f), WIDTH, HEIGHT,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "", calcCharSize(),
		sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));

	const float BUYHEIGHT = 40.f;

	if (!gameStats->unlocked.find("BLUE_PLAYER")->second) { //check if player bought character before
		buttons["PLAYER2BUY"]->setIdleColor(sf::Color(255, 106, 0, 255));
	}
	if (!gameStats->unlocked.find("DELOREAN_PLAYER")->second) {
		buttons["PLAYER3BUY"]->setIdleColor(sf::Color(255, 106, 0, 255));
	}
	if (!gameStats->unlocked.find("GAME_BACKGROUND_PINK")->second) { //check if player bought map before
		buttons["MAP2BUY"]->setIdleColor(sf::Color(255, 106, 0, 255));
	}
	if (!gameStats->unlocked.find("GAME_BACKGROUND_DESERT")->second) {
		buttons["MAP3BUY"]->setIdleColor(sf::Color(255, 106, 0, 255));
	}

	if (gameStats->playerTexture == "DEFAULT_PLAYER") { //to show which character the player previously chose
		buttons["PLAYER1"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["PLAYER1"]->setHoverColor(sf::Color(20, 20, 20, 50));
	}
	if (gameStats->playerTexture == "BLUE_PLAYER") {
		buttons["PLAYER2"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["PLAYER2"]->setHoverColor(sf::Color(20, 20, 20, 50));
	}
	if (gameStats->playerTexture == "DELOREAN_PLAYER") {
		buttons["PLAYER3"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["PLAYER3"]->setHoverColor(sf::Color(20, 20, 20, 50));
	}
	if (gameStats->theme == "GAME_BACKGROUND") { //to show which map the player previously chose
		buttons["MAP1"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["MAP1"]->setHoverColor(sf::Color(20, 20, 20, 50));
	}
	if (gameStats->theme == "GAME_BACKGROUND_PINK") {
		buttons["MAP2"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["MAP2"]->setHoverColor(sf::Color(20, 20, 20, 50));
	}
	if (gameStats->theme == "GAME_BACKGROUND_DESERT") {
		buttons["MAP3"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["MAP3"]->setHoverColor(sf::Color(20, 20, 20, 50));
	}

	player1.setTexture(textures->at("DEFAULT_PLAYER"));
	player1.setTextureRect(sf::IntRect(0, 0, 104, 107));
	player1.setPosition(p2pX(14.f), p2pY(22.f));

	player2.setTexture(textures->at("BLUE_PLAYER"));
	player2.setTextureRect(sf::IntRect(0, 0, 104, 107));
	player2.setPosition(p2pX(43.f), p2pY(22.f));

	player3.setTexture(textures->at("DELOREAN_PLAYER"));
	player3.setTextureRect(sf::IntRect(0, 0, 191, 107));
	player3.setPosition(p2pX(68.f), p2pY(22.f));

	map1.setTexture(textures->at("GAME_BACKGROUND"));
	map1.setPosition(p2pX(9.5f), p2pY(67.f));
	map1.setScale(0.084f, 0.084f);

	map2.setTexture(textures->at("GAME_BACKGROUND_PINK"));
	map2.setPosition(p2pX(39.f), p2pY(67.f));
	map2.setScale(0.17f, 0.17f);

	map3.setTexture(textures->at("GAME_BACKGROUND_DESERT"));
	map3.setPosition(p2pX(67.f), p2pY(67.f));
	map3.setScale(0.17f, 0.17f);
}

ShopState::ShopState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	GameStats* gameStats) :
	State(renderWindow, states, textures, fonts, soundBuffers),
	gameStats(gameStats), rotate(0), player1(), player2(), player3(),
	map1(), map2(), map3()
{
	initializeGUI();

	background.setTexture(textures->at("SHOP_BACKGROUND"));
	background.setScale(sf::Vector2f(static_cast<float>(renderWindow->getSize().x) / 3000.f,
		static_cast<float>(renderWindow->getSize().y) / 2000.f));
}

ShopState::~ShopState() {
}

void ShopState::updateMouseWheel(const short& mouseDelta) {
	// Any Unique Pause State Mouse Wheel Input
}

void ShopState::updateKeyboard(const sf::Keyboard::Key& keyCode) {
	if (sf::Keyboard::Key::Num4 == keyCode && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		gameStats->coins += 300;
	if (sf::Keyboard::Key::Escape == keyCode)
		quitState();
}

void ShopState::updateMouseButtons(const sf::Mouse::Button& button) {
	switch (button) {
	case sf::Mouse::Button::Left:

		//gameStats->playerTexture = "BLUE_PLAYER";
		//player.setTexture(textures->at(gameStats->playerTexture));
		for (auto& button : buttons) {
			button.second->checkBounds(mousePosView);
		}
	default:
		break;
	}
}

void ShopState::updateGUI() {
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons) {
		it.second->updateColor(mousePosView);
	}

	if (buttons["BACK"]->getIsActivated())
		quitState();

	if (buttons["PLAYER1"]->getIsActivated()) {
		gameStats->playerTexture = "DEFAULT_PLAYER";

		buttons["PLAYER1"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["PLAYER1"]->setHoverColor(sf::Color(20, 20, 20, 50));

		buttons["PLAYER2"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["PLAYER2"]->setHoverColor(sf::Color(74, 108, 135, 170));

		buttons["PLAYER3"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["PLAYER3"]->setHoverColor(sf::Color(74, 108, 135, 170));
	}
	if (buttons["PLAYER2"]->getIsActivated() && buttons.find("PLAYER2BUY") == buttons.end()) {
		gameStats->playerTexture = "BLUE_PLAYER";

		buttons["PLAYER1"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["PLAYER1"]->setHoverColor(sf::Color(74, 108, 135, 170));

		buttons["PLAYER2"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["PLAYER2"]->setHoverColor(sf::Color(20, 20, 20, 50));

		buttons["PLAYER3"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["PLAYER3"]->setHoverColor(sf::Color(74, 108, 135, 170));
	}
	if (buttons["PLAYER3"]->getIsActivated() && buttons.find("PLAYER3BUY") == buttons.end()) {
		gameStats->playerTexture = "DELOREAN_PLAYER";

		buttons["PLAYER1"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["PLAYER1"]->setHoverColor(sf::Color(74, 108, 135, 170));

		buttons["PLAYER2"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["PLAYER2"]->setHoverColor(sf::Color(74, 108, 135, 170));

		buttons["PLAYER3"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["PLAYER3"]->setHoverColor(sf::Color(20, 20, 20, 50));
	}
	if (buttons["MAP1"]->getIsActivated()) {
		gameStats->theme = "GAME_BACKGROUND";

		buttons["MAP1"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["MAP1"]->setHoverColor(sf::Color(20, 20, 20, 50));

		buttons["MAP2"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["MAP2"]->setHoverColor(sf::Color(74, 108, 135, 170));

		buttons["MAP3"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["MAP3"]->setHoverColor(sf::Color(74, 108, 135, 170));
	}
	if (buttons["MAP2"]->getIsActivated() && buttons.find("MAP2BUY") == buttons.end()) {
		gameStats->theme = "GAME_BACKGROUND_PINK";

		buttons["MAP1"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["MAP1"]->setHoverColor(sf::Color(74, 108, 135, 170));

		buttons["MAP2"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["MAP2"]->setHoverColor(sf::Color(20, 20, 20, 50));

		buttons["MAP3"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["MAP3"]->setHoverColor(sf::Color(74, 108, 135, 170));
	}
	if (buttons["MAP3"]->getIsActivated() && buttons.find("MAP3BUY") == buttons.end()) {
		gameStats->theme = "GAME_BACKGROUND_DESERT";

		buttons["MAP1"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["MAP1"]->setHoverColor(sf::Color(74, 108, 135, 170));

		buttons["MAP2"]->setIdleColor(sf::Color(100, 100, 100, 100));
		buttons["MAP2"]->setHoverColor(sf::Color(74, 108, 135, 170));

		buttons["MAP3"]->setIdleColor(sf::Color(20, 20, 20, 50));
		buttons["MAP3"]->setHoverColor(sf::Color(20, 20, 20, 50));
	}

	if (buttons.find("PLAYER2BUY") != buttons.end() && buttons["PLAYER2BUY"]->getIsActivated() && gameStats->coins >= 100) {
		gameStats->coins -= 100;
		gameStats->unlocked.find("BLUE_PLAYER")->second = true;
		coinAmount.setString(std::to_string(gameStats->coins));
		buttons.erase("PLAYER2BUY");
	}
	if (buttons.find("PLAYER3BUY") != buttons.end() && buttons["PLAYER3BUY"]->getIsActivated() && gameStats->coins >= 200) {
		gameStats->coins -= 200;
		gameStats->unlocked.find("DELOREAN_PLAYER")->second = true;
		coinAmount.setString(std::to_string(gameStats->coins));
		buttons.erase("PLAYER3BUY");
	}
	if (buttons.find("MAP2BUY") != buttons.end() && buttons["MAP2BUY"]->getIsActivated() && gameStats->coins >= 100) {
		gameStats->coins -= 100;
		gameStats->unlocked.find("GAME_BACKGROUND_PINK")->second = true;
		coinAmount.setString(std::to_string(gameStats->coins));
		buttons.erase("MAP2BUY");
	}
	if (buttons.find("MAP3BUY") != buttons.end() && buttons["MAP3BUY"]->getIsActivated() && gameStats->coins >= 200) {
		gameStats->coins -= 200;
		gameStats->unlocked.find("GAME_BACKGROUND_DESERT")->second = true;
		coinAmount.setString(std::to_string(gameStats->coins));
		buttons.erase("MAP3BUY");
	}

	if (rotate < 5) {
		player1.rotate(0.9f);
		player2.rotate(0.9f);
		player3.rotate(0.9f);
	}
	else if (rotate < 10) {
		player1.rotate(-0.9f);
		player2.rotate(-0.9f);
		player3.rotate(-0.9f);
	}
	else {
		if (rotate == 44) {
			rotate = -1;
		}
	}
	rotate++;
}

void ShopState::updateState(const float& deltaTime) {
	updateMousePositions();
	updateGUI();
}

void ShopState::renderState(std::shared_ptr<sf::RenderTarget> renderTarget) {
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);

	sf::Text title("SHOP", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(90);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);
	sf::RenderStates renderStates;
	renderTarget->draw(title, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 2.f -
		title.getGlobalBounds().width / 2.f, 0.f)));

	renderGUI(renderTarget);
}

// Render
void ShopState::renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget) {
	sf::RectangleShape coinBackground;
	coinBackground.setFillColor(sf::Color(0, 0, 0, 50));
	coinBackground.setSize(sf::Vector2f(200.f, 50.f));
	coinBackground.setPosition(1050, 25);
	renderWindow->draw(coinBackground);

	coinAmount = sf::Text(std::to_string(gameStats->coins), fonts->at("DOSIS-BOLD"));
	coinAmount.setCharacterSize(40);
	coinAmount.setStyle(sf::Text::Bold);
	coinAmount.setFillColor(sf::Color::White);
	coinAmount.setPosition(1140, 25);
	renderWindow->draw(coinAmount);

	Entity coinPic;
	coinPic.setTexture(textures->at("COIN"));
	coinPic.setPosition(1000, 12);
	coinPic.setScale(0.6f, 0.6f);
	renderWindow->draw(coinPic);

	for (auto& it : buttons) {
		it.second->draw(*renderTarget);
	}
	renderTarget->draw(player1);
	renderTarget->draw(player2);
	renderTarget->draw(player3);
	renderTarget->draw(map1);
	renderTarget->draw(map2);
	renderTarget->draw(map3);
}