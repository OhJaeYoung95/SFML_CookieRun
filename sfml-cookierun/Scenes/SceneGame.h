#pragma once
#include "Scene.h"

class Pancake;
class Pirate;
class Moonlighter;
class Player;
class PlayerTest;
class UIButton;
class Map;
class UIHp;
class TextGo;
class SpriteGo;
class Pause;
class SceneLobby;

class SceneGame : public Scene
{
protected:
	int coin = 0;
	int score = 0;
	int bestScore = 0;
	int diamond = 0;

	SceneLobby* scene;

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

	CookieTypes currentCookieType = Variables::CurrentCookieType;

	Pancake* pancake;
	Pirate* pirate;
	Moonlighter* moonlighter;

	Map* map;

	//UIButton* uiButton;
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


	int GetCoin() const { return coin; }
	int GetDia() const { return diamond; }
	int GetScore() const { return score; }
	int GetBestScore() const { return bestScore; }

	void SetScore(int score) { this->score = score; }
	void SetBestScore(int bestScore) { this->bestScore = bestScore; }

	void AddCoin(int value) { coin += value;}
	void AddScore(int value) { score += value; }
	void AddDia(int value) { diamond += value; }

	void JumpUIDown(bool isActive);
	void SlideUIDown(bool isActive);
	void IsChangeScene(bool isBool) { isChange = isBool; }

	void IsActiveGameOver(bool isActive);
	void SetScene(SceneLobby* scene) { this->scene = scene;}
};

