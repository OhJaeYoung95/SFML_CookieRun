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
class Pause;

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

	SpriteGo* jumpUpUI;
	SpriteGo* jumpDownUI;
	SpriteGo* slideUpUI;
	SpriteGo* slideDownUI;
	SpriteGo* pauseUIButton;	// 퍼즈를 걸기 위한 UI
	
	SpriteGo* hitEffect;

	Pancake* pancake;

	Player* player;
	PlayerTest* playerTest;

	Map* map;

	UIButton* uiButton;
	Pause* pauseUI;		// 실제 퍼즈 UI

	float jumpUIDownTimer = 0.f;
	float jumpUIDownDuration = 0.2f;
	bool isChange = false;

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

	void JumpUIDown(bool isActive);
	void SlideUIDown(bool isActive);
	void IsChangeTitle(bool isBool) { isChange = isBool; }
};

