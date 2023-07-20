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

	LobbyCookie* cookie;

	UIButton* playButton;
	TextGo* playText;

	UIButton* cookieStorageBox;
	TextGo* storageText;
	SpriteGo* storageImage;

	UIButton* cookieSkinBox;
	TextGo* skinText;
	SpriteGo* skinImage;

	StorageBox* storageUI;

public:
	SceneLobby();
	virtual ~SceneLobby() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

