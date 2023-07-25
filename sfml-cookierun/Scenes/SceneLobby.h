#pragma once
#include "Scene.h"
#include "LobbyCookie.h"

class Lobby;
class Cookie;
class SceneGame;
class UIButton;
class TextGo;
class SpriteGo;
class StorageBox;

class SceneLobby : public Scene
{
protected:
	SceneGame* scene;

	Lobby* lobby;

	// ���� ����
	SpriteGo* currentCoin;
	SpriteGo* coinBg;
	TextGo* coinText;
	int coin = 0;

	// ���̾� ����
	SpriteGo* currentDia;
	SpriteGo* diaBg;
	TextGo* diaText;
	int diamond = 0;

	LobbyCookie* cookie;

	// �÷��� ��ư
	UIButton* playButton;
	TextGo* playText;

	// �� ��Ű�� ��ư
	UIButton* cookieStorageBox;
	TextGo* storageText;
	SpriteGo* storageImage;

	// ��Ų ��ư
	UIButton* cookieSkinBox;
	TextGo* skinText;
	SpriteGo* skinImage;

	StorageBox* storageUI;

	bool isEnterPlay = false;

public:
	SceneLobby();
	virtual ~SceneLobby() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetCoin(int coin) { this->coin += coin; }
	void SetDia(int dia) { diamond += dia; }

	int GetCoin() { return coin; }
	int GetDia() { return diamond; }
};

