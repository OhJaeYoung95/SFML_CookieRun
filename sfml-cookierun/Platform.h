#pragma once
#include "SpriteGo.h"

class Cookie;

class Platform : public SpriteGo
{
protected:
	Cookie* cookie;

public:
	Platform(const std::string& textureId = "", const std::string& n = "");
	virtual ~Platform() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetCookie(Cookie*& cookie);
	void ColCookie();
};