#pragma once
#include "Scene.h"
#include "LobbyCookie.h"

class Lobby;
class Cookie;
class SceneGame;
class UIButton;
class TextGo;

class SceneLobby : public Scene
{
protected:
	// SceneMgr Init / Enter부분 살펴보기
	// SceneGame의 정보를 받아오는 순간에
	// SceneGame이 살아있나 체크
	SceneGame* scene;

	Lobby* lobby;

	LobbyCookie* cookie;

	UIButton* playButton;
	TextGo* playText;

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

