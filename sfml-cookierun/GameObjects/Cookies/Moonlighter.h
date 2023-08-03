#pragma once
#include "Cookie.h"
#include "AnimationController.h"

class Moonlighter : public Cookie
{
protected:
	AnimationController animation;

public:

	Moonlighter(const std::string& textureId = "", const std::string& n = "");
	virtual ~Moonlighter() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

