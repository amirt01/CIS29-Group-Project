#ifndef GAME_H
#define GAME_H

class Game
{
private:
	//Variables
	sf::RenderWindow* renderWindow;
	sf::Event event;

	sf::Clock deltaTimeClock;
	float deltaTime;

	//Initialization
	void initializeWindow();
	void initVariables();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDeltaTime();
	void updateSFMLEvents();
	void updateGame();

	//Render
	void renderGame();

	//Core
	void runGame();
};

#endif