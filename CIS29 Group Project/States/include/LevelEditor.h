#pragma once

#include "GameState.h"
#include "GUI.h"
#include "Object.h"

class LevelEditor : public GameState
{
private:
	float deltaTimeHolder;

	void updateSpawning() {};

public:
	// Constructors/Destructors
	LevelEditor(sf::RenderWindow* renderWindow, std::stack<State*>* states, std::map<std::string, sf::Texture>* textures);
	virtual ~LevelEditor();

	void updateKeyboard(unsigned short keyCode);
	void updateMouseWheel(short mouseDelta);
	void updateState(const float& deltaTime);
};
