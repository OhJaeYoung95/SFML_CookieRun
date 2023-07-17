#pragma once
#include "Scene.h"

class Pancake;
class Player;
class PlayerTest;
class UIButton;
class Map;
class UIHp;
class TextGo;
class SpriteGo;

class SceneGame : public Scene
{
protected:

	int coin = 99;
	int score = 90;

	// UI
	UIHp* hpUI;
	TextGo* coinText;
	TextGo* scoreText;

	SpriteGo* scoreJellyUI;
	SpriteGo* scoreCoinUI;

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

	void AddCoin(int value) { coin += value;}
	void AddScore(int value) { score += value; }
};

