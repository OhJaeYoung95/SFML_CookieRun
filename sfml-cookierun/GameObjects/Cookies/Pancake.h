#pragma once
#include "Cookie.h"
#include "AnimationController.h"

class Pancake : public Cookie
{
protected:
	AnimationController animation;

public:

	Pancake(const std::string& textureId = "", const std::string& n = "");
	virtual ~Pancake() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

