#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class LobbyCookie : public SpriteGo
{
protected:
	CookieTypes type = Variables::CurrentCookieType;
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

