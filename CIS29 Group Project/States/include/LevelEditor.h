#pragma once

#include "GameState.h"
#include "Button.h"
#include "Object.h"

class LevelEditor : public GameState
{
private:
	float deltaTimeHolder;

	void updateSpawning() {};

public:
	// Constructors/Destructors
	LevelEditor(sf::RenderWindow* renderWindow, std::stack<State*>* states,
		std::unordered_map<std::string, sf::Texture>* textures,
		std::unordered_map<std::string, sf::Font>* fonts,
		std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers);
	virtual ~LevelEditor();

	void updateKeyboard(unsigned short keyCode);
	void updateMouseWheel(short mouseDelta);
	void updateState(const float& deltaTime);
};
