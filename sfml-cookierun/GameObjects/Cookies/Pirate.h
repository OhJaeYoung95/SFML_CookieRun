#pragma once
#include "Cookie.h"
#include "AnimationController.h"

class Pirate : public Cookie
{
protected:
	AnimationController animation;

public:

	Pirate(const std::string& textureId = "", const std::string& n = "");
	virtual ~Pirate() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

