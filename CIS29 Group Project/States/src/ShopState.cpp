#include "stdafx.h"
#include "ShopState.h"

void ShopState::initializeGUI() {
	buttons["BACK"] = new gui::Button(1000, 600, 150, 50,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Back",
			sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["PLAYER1"] = new gui::Button(135, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	buttons["PLAYER2"] = new gui::Button(500, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	buttons["PLAYER3"] = new gui::Button(865, 200, 250, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));

	buttons["PLAYER2BUY"] = new gui::Button(500, 425, 200, 40,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "100",
			sf::Color(255, 106, 0, 255), sf::Color(255, 106, 0, 255), sf::Color(255, 106, 0, 200));
	buttons["PLAYER3BUY"] = new gui::Button(865, 425, 250, 40,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "200",
			sf::Color(255, 106, 0, 255), sf::Color(255, 106, 0, 255), sf::Color(255, 106, 0, 200));

	if (gameStats->unlocked.find("BLUE_PLAYER")->second == true) { //check if player bought before
		delete buttons["PLAYER2BUY"];
		buttons.erase("PLAYER2BUY");
	}
	if (gameStats->unlocked.find("DELOREAN_PLAYER")->second == true) {
		delete buttons["PLAYER3BUY"];
		buttons.erase("PLAYER3BUY");
	}


	if (gameStats->playerTexture == "DEFAULT_PLAYER") { //to show which character the player previously chose
		delete buttons["PLAYER1"];
		buttons["PLAYER1"] = new gui::Button(135, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50));
	}
	if (gameStats->playerTexture == "BLUE_PLAYER") {
		delete buttons["PLAYER2"];
		buttons["PLAYER2"] = new gui::Button(500, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50));
	}
	if (gameStats->playerTexture == "DELOREAN_PLAYER") {
		delete buttons["PLAYER3"];
		buttons["PLAYER3"] = new gui::Button(865, 200, 250, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50));
	}


	player1.setTexture(textures->at("DEFAULT_PLAYER"));
	player1.getSprite().setTextureRect(sf::IntRect(0, 0, 104, 107));
	player1.setPosition(185, 250);


	player2.setTexture(textures->at("BLUE_PLAYER"));
	player2.getSprite().setTextureRect(sf::IntRect(0, 0, 104, 107));
	player2.setPosition(550, 250);

	player3.setTexture(textures->at("DELOREAN_PLAYER"));
	player3.setPosition(880, 280);
}

ShopState::ShopState(sf::RenderWindow * renderWindow, std::stack<State *> * states,
					 std::unordered_map<std::string, sf::Texture> * textures,
					 std::unordered_map<std::string, sf::Font> * fonts,
					 std::unordered_map<std::string, sf::SoundBuffer> * soundBuffers,
					 GameStats * gameStats) :
	State(renderWindow, states, textures, fonts, soundBuffers),
	gameStats(gameStats), 
	rotate(0),
	player1(),
	player2(),
	player3()
{
	initializeGUI();

	background.getSprite().setTexture(textures->at("SHOP_BACKGROUND"));
	background.getSprite().setScale(sf::Vector2f(static_cast<float>(renderWindow->getSize().x)/3000,
									static_cast<float>(renderWindow->getSize().y)/2000));
}

ShopState::~ShopState() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

void ShopState::updateMouseWheel(const short & mouseDelta) {
	// Any Unique Pause State Mouse Wheel Input
}

void ShopState::updateKeyboard(const sf::Keyboard::Key & keyCode) {
	//if (sf::Keyboard::Key::G == keyCode)
	//	states->push(new FreePlayState(renderWindow, states, textures, fonts, soundBuffers, leaderboard));
}

void ShopState::updateMouseButtons(const sf::Mouse::Button & button) {
	switch (button) {
		case sf::Mouse::Button::Left:

		//gameStats->playerTexture = "BLUE_PLAYER";
		//player.setTexture(textures->at(gameStats->playerTexture));
		for (auto & button : buttons) {
			button.second->checkBounds(mousePosView);
		}
		default:
		break;
	}
}

void ShopState::updateGUI() {
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto & it : buttons) {
		it.second->updateColor(mousePosView);
	}

	if (buttons["BACK"]->getIsActivated())
		quitState();

	if (buttons["PLAYER1"]->getIsActivated()) {
		gameStats->playerTexture = "DEFAULT_PLAYER";
		delete buttons["PLAYER1"];
		delete buttons["PLAYER2"];
		delete buttons["PLAYER3"];
		buttons["PLAYER1"] = new gui::Button(135, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50));
		buttons["PLAYER2"] = new gui::Button(500, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
		buttons["PLAYER3"] = new gui::Button(865, 200, 250, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	}
	if (buttons["PLAYER2"]->getIsActivated() && buttons.find("PLAYER2BUY") == buttons.end()) {
		gameStats->playerTexture = "BLUE_PLAYER";
		delete buttons["PLAYER1"];
		delete buttons["PLAYER2"];
		delete buttons["PLAYER3"];
		buttons["PLAYER1"] = new gui::Button(135, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
		buttons["PLAYER2"] = new gui::Button(500, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50));
		buttons["PLAYER3"] = new gui::Button(865, 200, 250, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
	}
	if (buttons["PLAYER3"]->getIsActivated() && buttons.find("PLAYER3BUY") == buttons.end()) {
		gameStats->playerTexture = "DELOREAN_PLAYER";
		delete buttons["PLAYER1"];
		delete buttons["PLAYER2"];
		delete buttons["PLAYER3"];
		buttons["PLAYER1"] = new gui::Button(135, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
		buttons["PLAYER2"] = new gui::Button(500, 200, 200, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(100, 100, 100, 100), sf::Color(74, 108, 135, 170), sf::Color(20, 20, 20, 50));
		buttons["PLAYER3"] = new gui::Button(865, 200, 250, 200,
			&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "",
			sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50));
	}

	if (buttons.find("PLAYER2BUY") != buttons.end() && buttons["PLAYER2BUY"]->getIsActivated() && gameStats->coins >= 100) {
		gameStats->coins -= 100;
		gameStats->unlocked.find("BLUE_PLAYER")->second = true;
		delete buttons["PLAYER2BUY"];
		buttons.erase("PLAYER2BUY");
	}
	if (buttons.find("PLAYER3BUY") != buttons.end() && buttons["PLAYER3BUY"]->getIsActivated() && gameStats->coins >= 200) {
		gameStats->coins -= 200;
		gameStats->unlocked.find("DELOREAN_PLAYER")->second = true;
		delete buttons["PLAYER3BUY"];
		buttons.erase("PLAYER3BUY");
	}


	if (rotate < 5) {
		player1.getSprite().rotate(0.9f);
		player2.getSprite().rotate(0.9f);
		player3.getSprite().rotate(0.9f);
	} else if (rotate < 10){
		player1.getSprite().rotate(-0.9f);
		player2.getSprite().rotate(-0.9f);
		player3.getSprite().rotate(-0.9f);
	} else {
		if (rotate == 44) {
			rotate = -1;
		}
	}
	rotate++;
	//// Updates all the buttons in the state and handles their functionality
	//for (auto & it : buttons) {
	//	it.second->updateColor(mousePosView);
	//}

}

void ShopState::updateState(const float & deltaTime) {
	updateMousePositions();
	updateGUI();
}


void ShopState::renderState(sf::RenderTarget * renderTarget) {
	if (!renderTarget)
		renderTarget = renderWindow;

	background.render(renderTarget);

	sf::Text title("SHOP", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(128);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);
	sf::RenderStates renderStates;
	renderTarget->draw(title, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 2.f -
																			title.getGlobalBounds().width / 2.f, 0.f)));
	
	
	renderGUI(renderTarget);
}

// Render
void ShopState::renderGUI(sf::RenderTarget * renderTarget) {
	
	sf::RectangleShape coinBackground;
	coinBackground.setFillColor(sf::Color(0, 0, 0, 50));
	coinBackground.setSize(sf::Vector2f(200.f, 50.f));
	coinBackground.setPosition(1050, 80);
	renderWindow->draw(coinBackground);
	
	sf::Text coinAmount(std::to_string(gameStats->coins), fonts->at("DOSIS-BOLD"));
	coinAmount.setCharacterSize(40);
	coinAmount.setStyle(sf::Text::Bold);
	coinAmount.setFillColor(sf::Color::White);
	coinAmount.setPosition(1150, 80);
	renderWindow->draw(coinAmount);

	Entity coinPic;
	coinPic.setTexture(textures->at("COIN"));
	coinPic.setPosition(1000, 60);
	coinPic.getSprite().setScale(0.65f, 0.65f);
	coinPic.render(renderTarget);

	for (auto & it : buttons) {
		it.second->draw(*renderTarget);
	}
	player1.render(renderTarget);
	player2.render(renderTarget);
	player3.render(renderTarget);
}
