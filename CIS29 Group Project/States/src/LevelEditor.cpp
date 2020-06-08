#include "stdafx.h"
#include "LevelEditor.h"

LevelEditor::LevelEditor(sf::RenderWindow* renderWindow, std::stack<State*>* states, std::map<std::string, sf::Texture>* textures)
	: GameState(renderWindow, states, textures)
{
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::updateKeyboard(unsigned short keyCode)
{
	switch (keyCode)
	{
	case sf::Keyboard::Escape:
		quitState();
		break;
	case sf::Keyboard::Left:
		updateBackground(deltaTimeHolder, -1);
		break;
	case sf::Keyboard::Right:
		updateBackground(deltaTimeHolder, 1);
	default:
		break;
	}
}

void LevelEditor::updateMouseWheel(short mouseDelta)
{
	updateBackground(deltaTimeHolder, mouseDelta);
}

void LevelEditor::updateState(const float& deltaTime)
{
	deltaTimeHolder = deltaTime;
	updateSpawning();

	if (!objects.empty())
	{
		checkCollision();
		updateObjects(deltaTime);
	}
}