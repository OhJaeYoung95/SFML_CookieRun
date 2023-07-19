#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

enum class LobbyCookieType
{
	None = -1,
	Pancake,
	Pirate,
	Moonlighter,
};

class LobbyCookie : public SpriteGo
{
protected:
	AnimationController animation;

public:
	LobbyCookie(const std::string& textureId = "", const std::string& n = "");
	virtual ~LobbyCookie() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

