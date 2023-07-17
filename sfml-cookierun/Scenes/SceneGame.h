#pragma once
#include "Scene.h"

class Pancake;
class Player;
class PlayerTest;
class UIButton;
class Map;
class UIHp;

class SceneGame : public Scene
{
protected:


	UIHp* hpUI;

	Pancake* pancake;

	Player* player;
	PlayerTest* playerTest;

	Map* map;

	UIButton* uiButton;

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

