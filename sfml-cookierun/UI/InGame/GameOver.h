#pragma once
#include "SpriteGo.h"

class TextGo;
class UIButton;
class SceneGame;

class GameOver : public SpriteGo
{
protected:
	SceneGame* scene;

	sf::RectangleShape bg;	// Èæ¹é
	TextGo* gameOverText;
	TextGo* bestScore;
	TextGo* currentScore;

	SpriteGo* gameOverBg;

	UIButton* restartButton;
	UIButton* exitButton;

public:
	GameOver(const std::string& textureId = "", const std::string& n = "");
	virtual ~GameOver() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetSceneGame(SceneGame* scene) { this->scene = scene; }
	void IsActiveGameOver(bool isActive);

	void TextInit(TextGo* text, sf::Vector2f pos, int size);
	void UIInit(UIButton* button, sf::Vector2f pos, sf::Vector2f size);
	
	void ButtonEvent(UIButton* button);
};