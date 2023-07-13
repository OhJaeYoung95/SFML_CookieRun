#pragma once
#include "SpriteGo.h"
class Platform : public SpriteGo
{
protected:

public:
	Platform(const std::string& textureId = "", const std::string& n = "");
	virtual ~Platform() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};