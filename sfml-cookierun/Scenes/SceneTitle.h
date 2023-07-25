#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class UIButton;

class SceneTitle : public Scene
{
protected:
	SpriteGo* bg;
	SpriteGo* frame;

	TextGo* title1;
	TextGo* title2;

	TextGo* info;

	UIButton* startBtn;
	UIButton* editorBtn;

public:
	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void ButtonInit(UIButton* btn, sf::Vector2f pos, sf::Vector2f size, SceneId id);
};

