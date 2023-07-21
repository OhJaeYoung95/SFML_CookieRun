#pragma once
#include "SpriteGo.h"
class UIButton;
class SceneLobby;
class TextGo;

class StorageBox : public SpriteGo
{
protected:
	sf::RectangleShape bg;

	SpriteGo* storageBoxBG;

	UIButton* pancakeButton;
	UIButton* pirateButton;
	UIButton* moonlighterButton;

	TextGo* pancakeLockText;
	TextGo* pirateLockText;
	TextGo* moonlighterLockText;

	SceneLobby* scene;


public:
	StorageBox(const std::string& textureId = "", const std::string& n = "");
	virtual ~StorageBox() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetScene(SceneLobby* scene) { this->scene = scene; }
	void AllSetActive(bool isActive);

};

