#pragma once
#include "SpriteGo.h"

class UIButton;
class SceneGame;
class TextGo;

class Pause : public SpriteGo
{
protected:
	sf::RectangleShape bg;

	UIButton* continueButton;
	UIButton* exitButton;
	UIButton* redoButton;

	TextGo* pauseText;
	TextGo* continueText;
	TextGo* exitText;
	TextGo* redoText;

	SceneGame* scene;
	

public:
	Pause(const std::string& textureId = "", const std::string& n = "");
	virtual ~Pause() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetScene(SceneGame* scene) { this->scene = scene; }
	void AllSetActive(bool isActive);
};

