#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Cookie;

class UIHp : public SpriteGo
{
protected:
	AnimationController animation1;
	AnimationController animation2;
	Cookie* cookie;

	sf::Sprite hpBack;

	float timer = 0.f;
	float duration = 1.3f;

	float decreaseHp = 0.f;
	float decreaseMaxHp = 100.f;

public:

	UIHp(const std::string& textureId = "", const std::string& n = "");
	virtual ~UIHp() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetCookie(Cookie*& cookie) { this->cookie = cookie; }
};

