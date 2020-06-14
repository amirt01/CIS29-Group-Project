#pragma once
#include "State.h"
#include "Button.h"
#include "Entity.h"
#include "GameStats.h"

class ShopState :
	public State {
private:
	//Variables
	Entity background;
	std::map<std::string, gui::Button *> buttons;

	void initializeGUI();



	Entity player1;
	Entity player2;
	Entity player3;

	GameStats * gameStats;
	sf::Text coinAmount;

	int rotate;

public:

	ShopState(sf::RenderWindow * renderWindow, std::stack<State *> * states,
			  std::unordered_map<std::string, sf::Texture> * textures,
			  std::unordered_map<std::string, sf::Font> * fonts,
			  std::unordered_map<std::string, sf::SoundBuffer> * soundBuffers,
			  GameStats * gameStats);
	~ShopState();


	void updateMouseWheel(const short & mouseDelta);
	void updateKeyboard(const sf::Keyboard::Key & keyCode);
	void updateMouseButtons(const sf::Mouse::Button & button);
	void updateGUI();
	void updateState(const float & deltaTime);
	void renderState(sf::RenderTarget * renderTarget);
	void renderGUI(sf::RenderTarget * renderTarget);

};

