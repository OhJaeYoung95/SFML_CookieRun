#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

enum class LobbyType
{
	None = -1,
	Temple,
	WizardryTower,
	Cathedral,
};

class Lobby : public SpriteGo
{
protected:
	LobbyType type = LobbyType::None;

	AnimationController animation;
	AnimationController animationEffect1;

public:
	Lobby(const std::string& textureId = "", const std::string& n = "");
	virtual ~Lobby() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void SetType(LobbyType type) { this->type = type; }
	LobbyType GetType() { return type; }
};

