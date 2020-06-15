#pragma once
#include "State.h"
#include "Button.h"
#include "Entity.h"
#include "GameStats.h"

//note: $ = backdoor to add more coins to shop

class ShopState :
	public State {
private:
	//Variables
	Entity background;
	std::map<std::string, std::unique_ptr<gui::Button>> buttons;

	void initializeGUI();

	Entity player1;
	Entity player2;
	Entity player3;
	Entity map1;
	Entity map2;
	Entity map3;

	GameStats * gameStats;
	sf::Text coinAmount; 

	int rotate;

public:

	ShopState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>> * states,
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
	void renderGUI(std::shared_ptr<sf::RenderTarget> renderTarget);
	void renderState(std::shared_ptr<sf::RenderTarget> renderTarget);

};

