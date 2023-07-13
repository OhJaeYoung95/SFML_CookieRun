#pragma once
#include "SpriteGo.h"
class Background : public SpriteGo
{
protected:

public:
	Background(const std::string& textureId = "", const std::string& n = "");
	virtual ~Background() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

