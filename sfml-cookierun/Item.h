#pragma once
#include "SpriteGo.h"

class Cookie;

class Item : public SpriteGo
{
protected:
	Cookie* cookie;

public:
	Item(const std::string& textureId, const std::string& n);
	virtual ~Item() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	bool IsColPlayer();
};

